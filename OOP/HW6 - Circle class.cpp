#include <iostream>

using namespace std;

class Circle
{
	private:
		int x, y;
		float radius;
		const double PI;
	
	public:
		Circle() : PI(3.14159)
		{
			this->set_x(0);
			this->set_y(0);
			this->set_radius(5);
		}
		Circle(int x, int y, float radius) : PI(3.14159)
		{
			this->set_x(x);
			this->set_y(y);
			this->set_radius(radius);
		}
		Circle(int x, int y) : PI(3.14159)
		{
			this->set_x(x);
			this->set_y(y);
			
			this->set_radius(5);
		}
		Circle(const Circle &circle) : PI(3.14159)
		{
			this->set_x(circle.x);
			this->set_y(circle.y);
			this->set_radius(circle.radius);
		}
		
		~Circle()
		{
			cout << "Destructor\n";
		}
		
		/** SETTERS **/
		void set_x(const int x)
		{
			(x >= -50 && x <= 50) ? this->x = x : this->x = 0;
		}
		
		void set_y(const int y)
		{
			(y >= -50 && y <= 50) ? this->y = y : this->y = 0;
		}
		
		void set_radius(const float radius)
		{
			(radius >= 1 && radius <= 10) ? this->radius = radius : this->radius = 5;
		}
		
		/** GETTERS **/
		int get_x() const
		{
			return this->x;
		}
		
		int get_y() const
		{
			return this->y;
		}
		
		float get_radius() const
		{
			return this->radius;
		}
		
		/** OTHERS **/
		void set_circle(int x, int y, float radius)
		{
			this->set_x(x);
			this->set_y(y);
			this->set_radius(radius);
		}
		
		void get_circle()
		{
			int x, y;
			float radius;
			
			cout << "Enter x-coordinate: ";
			cin >> x;
			
			cout << "Enter y-coordinate: ";
			cin >> y;
			
			cout << "Enter radius: ";
			cin >> radius;
			
			this->set_circle(x, y, radius);
		}
		
		void put_circle() const
		{
			cout << "x-coordinate: " << this->get_x() << endl;
			cout << "y-coordinate: " << this->get_y() << endl;
			cout << "Radius: " << this->get_radius() << endl;
		}
		
		double get_area() const
		{
			return this->PI * this->get_radius() * this->get_radius();
		}
		
		float get_diameter() const
		{
			return this->get_radius() * 2;
		}
		
		double get_circumference() const
		{
			return 2 * this->PI * this->get_radius();
		}
		
		Circle add_circle(const Circle &c1, const Circle &c2) const
		{
			Circle c(
				c1.get_x() + c2.get_x(),
				c1.get_y() + c2.get_y(),
				c1.get_radius() + c2.get_radius()
			);
			
			return c;
		}
		
		bool is_equal(const Circle &c1, const Circle &c2) const
		{
			return c1.get_x() == c2.get_x()
				&& c1.get_y() == c2.get_y()
				&& c1.get_radius() == c2.get_radius();
		}
		
		int find_circle(const Circle circles[], int size) const
		{
			for (int i = 0; i < size; i++)
				if (this->is_equal(circles[i], *this))
					return i;
			return -1;
		}
		
		void update_objects(Circle circles[], int size)
		{
			for (int i = 0; i < size; i++)
				if (circles[i].get_x() == this->get_x() && circles[i].get_y() == this->get_y())
					circles[i].set_radius(this->get_radius());
		}
};

int main (void)
{
	Circle circles[5] = {
		Circle(2, 1, 1),
		Circle(1, 1, 1),
		Circle(1, 1, 1),
		Circle(2, 1, 1),
		Circle(2, 1, 1)
	};
	
	Circle circle(1, 1, 3);
	
	circle.update_objects(circles, 5);
	
	for (int i = 0; i < 5; i++)
	{
		circles[i].put_circle();
		cout << endl;
	}
	
	return 0;
}
