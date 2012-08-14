#ifndef JS_GEOMETRY_H
#define JS_GEOMETRY_H

#include <climits>
#include <cmath>
#include <vector>

namespace geometry {

  //Definition of PI
	const double PI = 3.14159265;

  //Point definition
	struct Point {
		double	x;
		double	y;
		Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
	};

  //Change to just rect
  struct Rectangle {
    Point p;
    int w;
    int h;
    Rectangle(Point _p, int _w, int _h) :
    p(_p), w(_w), h(_h) {};
  };
  
  //Shape Definition
	typedef std::vector<Point> Shape;

  //Vector definition
	class Vector {
	public:
		Vector(double x, double y) {
			this->p.x = x;
			this->p.y = y;
		};
		Vector(Point p) {
			this->p.x = p.x;
			this->p.y = p.y;
		};
		inline double x(void) {
			return p.x;
		};
		inline double y(void) {
			return p.y;
		};
		inline double Magnitude(void) {
			return sqrt( pow(p.x, 2) + pow(p.y, 2));
		};
		inline void Normalise(void) {
			double mag =  Magnitude();
			p.x = p.x/mag;
			p.y = p.y/mag;
		};
		inline void Addition(Vector& b) {
			p.x = p.x + b.x();
			p.y = p.y + b.y();
		};
		inline void Subtraction(Vector& b) {
			p.x = p.x - b.x();
			p.y = p.y - b.y();
		};
		inline void ScalerMultiply(const double r) {
			p.x = p.x * r;
			p.y = p.y * r;
		};
	private:
		Point p;
	};

	//Compare 2 Points
	static inline bool compare(Point p1, Point p2) {
		return (p1.x == p2.x && p1.y == p2.y);
	}

  //Get Straight line distance
	static inline double straightLineDistance(const Point p1, const Point p2) {
		return sqrt( pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2) );
	}

	//Check if a point lies in a polygon
	static inline bool pointInPolygon(Shape shape, Point p) {
		if (shape.empty()) {
			return false;
		}

		unsigned int i;
		unsigned int j = shape.size() - 1;
		bool oddnodes = false;

		for(i = 0; i < shape.size(); i++) {
			if((shape[i].y < p.y && shape[j].y >= p.y)
				|| (shape[j].y < p.y && shape[i].y >= p.y)) {
					if(shape[i].x + (p.y - shape[i].y) /
						(shape[j].y - shape[i].y)*(shape[j].x - shape[i].x) < p.x) {
						oddnodes = !oddnodes;
					}
			}
			j = i;
		}

		return oddnodes;
	}

	//Check if a point lies in a circle
	static inline bool pointInCircle(Point centre, double radius, Point p) {
		return straightLineDistance(centre, p) <= radius;
	}

  //Round function
	static inline int round(const double x) {
		return (int)(x + 0.5);
	}

  //Next power of two
	static inline int nextPowerofTwo(const int x) {
		double logbase2 = log((double)x) / log((double)2);
		return round(pow(2,ceil(logbase2)));
	}

  //Get point from polar
	static inline Point fromPolar(const Point centre, const double length, const double angle) {
		double xc = length * cos(angle) + centre.x;
		double yc = length * sin(angle) + centre.y;
		Point newpoint;
		newpoint.x = xc;
		newpoint.y = yc;
		return (newpoint);
	}

  //Degrees to radians conversion
	static inline double toRadian(const double degree) {
		return ((degree)/180*PI);
	}

  //Returns dot product of two vectors
	static inline double dotProduct( Vector& a, Vector& b) {
		return ((a.x() * b.x()) + (a.y() * b.y()));
	}

  /*
  Get sign of number

  Returns +1 if positive
  Returns -1 if negative
  Returns 0 if zero
	*/
	static inline int getSign(double num) {
		if (num > 0 ) return 1;
		else if (num == 0) return 0;
		else return -1;
	}
}

#endif // GEOMETRY_H
