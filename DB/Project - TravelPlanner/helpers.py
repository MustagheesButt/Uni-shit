import urllib.request
from urllib.parse import urlparse, urljoin

from flask import redirect, render_template, request, session, url_for
from functools import wraps

def login_required(f):
    """
    Decorate routes to require login.

    http://flask.pocoo.org/docs/1.0/views/#decorating-views
    """
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") is None:
            return redirect(url_for("login", next=request.url))
        return f(*args, **kwargs)
    return decorated_function

def is_safe_url(target):
    ref_url = urlparse(request.host_url)
    test_url = urlparse(urljoin(request.host_url, target))
    return test_url.scheme in ('http', 'https') and \
        ref_url.netloc == test_url.netloc

def get_neighbours(place_id, db_conn):
    return db_conn.execute('SELECT neighbour_id FROM Neighbours WHERE place_id = {}'.format(place_id))

def get_optimal_path(places, db_conn):
    start = places[0]
    goal = places[len(places) - 1]

    # Build graph
    graph = build_graph_incomplete(places, db_conn)

    queue = [(start, [start])]

    while queue:
        (vertex, path) = queue.pop(0)

        if vertex not in graph:
            graph = {**graph, **build_graph_incomplete([vertex], db_conn)}

        for next in graph[vertex] - set(path):
            if next == goal:
                #if is_slice_in_list(places, path + [next]):
                return path + [next]
            else:
                queue.append((next, path + [next]))

def get_path_cost(path, db_conn):
    total_cost = 0
    for i in range(len(path) - 1):
        val = db_conn.execute('SELECT neighbour_cost FROM Neighbours WHERE place_id = {} AND neighbour_id = {}'.format(path[i], path[i + 1]))
        print(val)
        total_cost += int(val[0]['neighbour_cost'])
    return total_cost

def get_path_travel_time(path, db_conn):
    total_time = 0
    for i in range(len(path) - 1):
        val = db_conn.execute('SELECT neighbour_time FROM Neighbours WHERE place_id = {} AND neighbour_id = {}'.format(path[i], path[i + 1]))
        total_time += int(val[0]['neighbour_time'])
    return total_time

def get_last_id(db_conn, col_name, table_name):
    x = db_conn.execute('SELECT MAX({}) as last_insert_id FROM {}'.format(col_name, table_name))[0]['last_insert_id']
    last_booking_id = 0 if x is None else x
    return last_booking_id

def build_graph_incomplete(places, db_conn):
    graph = {}
    for place in places:
        neighbour_ids = []
        for neighbour in get_neighbours(place, db_conn):
            neighbour_ids.append(neighbour['neighbour_id'])

        graph[place] = set(neighbour_ids)
    return graph

def build_graph(places, db_conn, graph={}):
    for place in places:
        if place in graph:
            continue
        else:
            neighbour_ids = []
            for neighbour in get_neighbours(place, db_conn):
                neighbour_ids.append(neighbour['neighbour_id'])

            graph[place] = set(neighbour_ids)

            graph = {**graph, **build_graph(graph[place], db_conn, graph)}

    return graph

def is_slice_in_list(s, l):
    len_s = len(s)  # so we don't recompute length of s on every iteration
    return any(s == l[i:len_s+i] for i in range(len(l) - len_s+1))
