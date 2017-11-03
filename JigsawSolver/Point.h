#ifndef _POINT_H_
#define _POINT_H_

/**
* Point.h
*
* Define a Point in range [-128, -128] to [127, 127]
*
* ! initialize on create
* ! internal modify only
*/
class Point {
	// friend class Piece;
protected:
	int8_t px, py;
#ifndef NDEBUG
	bool init;
#endif // DEBUG

public:
#ifndef NDEBUG
	// default constructor
	inline Point() : init(false) {}
	// constructor
	inline Point(int8_t x, int8_t y) : px(x), py(y), init(true) {}
#else
	// default constructor
	inline Point() {}
	// constructor
	inline Point(int8_t x, int8_t y) : px(x), py(y) {}
#endif // !NDEBUG

	// get Point.X
	inline int8_t getX() {
		assert(init);
		return px;
	}

	// get Point.Y
	inline int8_t getY() {
		assert(init);
		return py;
	}

	// copy
	// the default copy is good enough, no need to write a new one

	// add two Point
	inline void operator+=(Point& point) {
		assert(init);
		px += point.px;
		py += point.py;
	}

	// subtract two Point
	inline void operator-=(Point& point) {
		assert(init);
		px -= point.px;
		py -= point.py;
	}
};

#endif // !_POINT_H_
