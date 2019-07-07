from flask import Flask, flash, redirect, request, render_template, session, url_for, abort, jsonify
from flask_session import Session
from tempfile import mkdtemp
from datetime import date
from passlib.hash import bcrypt

from cs50 import SQL
from helpers import *

app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# connect to database
# parameters are in the format: driver://username:password@server[:port]/database_name
db = SQL("oracle+cx_oracle://TRAVEL_PLANNER:travel@localhost:1521/xe")

@app.route('/', methods=['GET'])
def index():
    return render_template("index.html")

@app.route('/signup', methods=['GET', 'POST'])
def signup():
    if request.method == 'POST':
        first_name = request.form['firstname']
        last_name = request.form['lastname']
        email = request.form['email']
        phone = request.form['phone']
        passwd = request.form['password']
        hashed_passwd = bcrypt.hash(passwd) # password encrypted using bcrypt
        confirm_passwd = request.form['confirm-password']

        if passwd != confirm_passwd:
            return redirect(url_for('signup'))

        last_user_id = get_last_id(db, 'user_id', 'Users')
        user_id = last_user_id + 1

        db.execute('INSERT INTO Users (user_id, user_first_name, user_last_name,'
                   'user_email, user_phone, user_password, user_registered_on)'
                   'VALUES ({}, \'{}\', \'{}\', \'{}\', \'{}\', \'{}\', TO_DATE(\'{}\', \'yyyy-mm-dd\'))'
                   .format(user_id, first_name, last_name, email, phone, hashed_passwd, date.today()))

        session['user_id'] = user_id
        session['first_name'] = first_name
        session['last_name'] = last_name
        session['email'] = email

        return redirect(url_for('dashboard'))
    elif request.method == 'GET':
        return render_template("signup.html")

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        passwd = request.form['password']

        user_data = db.execute('SELECT * FROM Users WHERE user_email = \'{}\''.format(email))[0]
        hashed_passwd = user_data['user_password']

        if not bcrypt.verify(passwd, hashed_passwd):
            return redirect(url_for('login'))

        session['user_id'] = user_data['user_id']
        session['first_name'] = user_data['user_first_name']
        session['last_name'] = ['user_last_name']
        session['email'] = email

        return redirect(url_for('dashboard'))
    elif request.method == 'GET':
        #session['user_id'] = '1'
        return render_template("login.html")

@app.route('/logout', methods=['GET'])
def logout():
    session.clear()
    return redirect('/')

@app.route('/dashboard', methods=['GET'])
@login_required
def dashboard():
    places_list = db.execute('SELECT * FROM Places')
    places_list = sorted(places_list, key=lambda k : k['place_name'])

    packages_list = db.execute('SELECT * FROM Packages')

    return render_template("dashboard.html", places=places_list, packages=packages_list)

@app.route('/account', methods=['GET'])
def account():
    bookings = db.execute('SELECT * FROM Bookings WHERE user_id = {}'.format(session['user_id']))
    packages = db.execute('SELECT * FROM Packages')
    return render_template("account.html", bookings=bookings, packages=packages)

@app.route('/booking', methods=['POST'])
def booking():
    # 1. get user input from request.form
    package_id = request.form['package']
    total_people = request.form['total_people']
    destinations = request.form.getlist('destinations[]')
    stay_durations = request.form.getlist('stay_durations[]')

    package_factor = db.execute('SELECT package_factor FROM Packages WHERE package_id = {}'
                                .format(package_id))[0]['package_factor']

    total_stay_duration = 0
    for sd in stay_durations:
        total_stay_duration += int(sd)

    # 2. calculate optimal path. Then derive total duration and travel time of that path
    destinations = [int(x) for x in destinations]
    optimal_path = get_optimal_path(destinations, db)

    standard_charges = get_path_cost(optimal_path, db)
    total_charges = standard_charges * package_factor

    travel_time = get_path_travel_time(optimal_path, db)
    total_duration = travel_time + total_stay_duration

    # 3. store booking data in Bookings table
    last_id = get_last_id(db, 'booking_id', 'Bookings')
    booking_id = last_id + 1

    db.execute('INSERT INTO Bookings (booking_id, user_id, package_id, booking_date, booking_total_people, '
               'booking_total_charges, booking_total_duration) '
               'VALUES ({}, {}, {}, TO_DATE(\'{}\', \'yyyy-mm-dd\'), {}, {}, {})'
               .format(booking_id, session.get('user_id'), package_id, date.today(), total_people,
                       total_charges, total_duration))

    # 4. Store each booking destination and its stay duration in Booking_destinations table
    for i in range(len(destinations)):
        db.execute('INSERT INTO Booking_destinations (booking_id, place_id, bd_stay_duration)'
                   'VALUES ({}, {}, {})'
                   .format(booking_id, destinations[i], stay_durations[i]))

    # 5. redirect to booking confirmation page
    return redirect(url_for('booking_confirmed', booking_id=booking_id))

@app.route('/booking-confirmed/<booking_id>', methods=['GET'])
def booking_confirmed(booking_id):
    # TODO: Make simple success notification page
    return "You have booked successfully!"

@app.route('/contact', methods=['GET'])
def contact_us():
    return render_template("contact-us.html")

@app.route('/about', methods=['GET'])
def about_us():
    return render_template("about-us.html")

@app.route('/test')
def test():
    data = get_optimal_path([1, 14], db)
    return str(data)

# APIs #
@app.route('/get-cost', methods=['POST'])
def get_cost():
    destinations = [int(x) for x in request.form.getlist('destinations[]')]
    optimal_path = get_optimal_path(destinations, db)
    total_cost = 0
    j = 2
    for i in range(len(optimal_path) - 1):
        total_cost += get_path_cost(optimal_path[i:j], db)
        j=j+1

    return str(total_cost)

@app.route('/get-travel-time', methods=['POST'])
def get_travel_time():
    destinations = [int(x) for x in request.form.getlist('destinations[]')]
    optimal_path = get_optimal_path(destinations, db)
    total_time = 0
    j = 2
    for i in range(len(optimal_path) - 1):
        total_time += get_travel_time(optimal_path[i:j], db)
        j=j+1
    return str(total_time)
