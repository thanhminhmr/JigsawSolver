#ifndef _POINT_H_
#define _POINT_H_

/**
* Point.h
*
* Define a Point in range [-128, -128] to [127, 127]
*
* ! initialize on create
* ! read - only
*/
class Point {
public:
	const int8_t x, y;

	// default constructor
	inline Point() : x(0), y(0) {}
	// constructor
	inline Point(int8_t x, int8_t y) : x(x), y(y) {}
	// copy constructor
	inline Point(const Point& p) : x(p.x), y(p.y) {}
	// copy operator
	inline void operator=(const Point& p) {
		this->~Point();
		new(this) Point(p);
	}

	// misc, compare two Point
	inline bool operator==(const Point& p) const {
		return x == p.x && y == p.y;
	}
	// misc, compare two Point
	inline bool operator!=(const Point& p) const {
		return x != p.x || y != p.y;
	}
};

#endif // !_POINT_H_
