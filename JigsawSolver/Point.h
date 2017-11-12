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
	union {
		struct {
			const int16_t x, y;
		};
		const int32_t data;
	};

	// default constructor
	inline Point() : x(0), y(0) {}
	// constructor
	inline Point(int16_t x, int16_t y) : x(x), y(y) {}
	// copy constructor
	inline Point(const Point& point) : data(point.data) {}
	// copy operator
	inline void operator=(const Point& point) {
		this->~Point();
		new(this) Point(point);
	}

	// misc, compare two Point
	inline bool operator==(const Point& point) const {
		return data == point.data;
	}
	// misc, compare two Point
	inline bool operator!=(const Point& point) const {
		return data != point.data;
	}
};

#endif // !_POINT_H_
