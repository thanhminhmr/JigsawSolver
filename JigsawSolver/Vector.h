#ifndef _VECTOR_H_
#define _VECTOR_H_

/**
* Vector.h
*
* Define a Vector in range [-128, -128] to [127, 127]
*
* ! initialize on create
* ! read - only
*/
class Vector {
public:
	const int8_t x, y;

	// default constructor
	inline Vector() : x(0), y(0) {}
	// constructor
	inline Vector(int8_t x, int8_t y) : x(x), y(y) {}
	// constructor, create vector AB
	inline Vector(Point a, Point b) : x(b.x - a.x), y(b.y - a.y) {}
	// copy constructor
	inline Vector(const Vector& v) : x(v.x), y(v.y) {}
	// copy operator
	inline void operator=(const Vector& v) {
		this->~Vector();
		new(this) Vector(v);
	}

	// move a Point with this Vector
	inline Point move(const Point& p) const {
		return Point(p.x + x, p.y + y);
	};

	// misc, compare two Vector
	inline bool operator==(const Vector& v) const {
		return x == v.x && y == v.y;
	}
	// misc, compare two Vector
	inline bool operator!=(const Vector& v) const {
		return x != v.x || y != v.y;
	}
};

#endif // !_VECTOR_H_
