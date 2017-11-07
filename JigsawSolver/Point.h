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
	// copy
	// the default copy is good enough, no need to write a new one

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
