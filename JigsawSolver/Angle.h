#ifndef _ANGLE_H_
#define _ANGLE_H_

/**
* Angle.h
*
* Define a Angle
*
* ! initialize on create
* ! read - only
*/
class Angle {
public:
	const Vector start, end;
	// default constructor
	inline Angle() : start(), end() {}
	// constructor
	inline Angle(Point prev, Point current, Point next) : start(current, next), end(current, prev) {}
	// constructor, Angle 
	inline Angle(Vector a, Vector b) : start(a), end(b) {}
	// copy constructor
	inline Angle(const Angle& p) : start(p.start), end(p.end) {}
	// copy operator
	inline void operator=(const Vector& v) {
		new(this) Vector(v);
	}

	// get the angle between [-pi, +pi] radians
	inline float toRad() const {
		// dot product between[x1, y1] and [x2, y2]
		int32_t dot = (int32_t) start.x * (int32_t) end.x + (int32_t) start.y * (int32_t) end.y;
		// determinant
		int32_t det = (int32_t) start.x * (int32_t) end.y - (int32_t) start.y * (int32_t) end.x;
		// atan2(y, x) or atan2(sin, cos)
		return atan2f((float) det, (float) dot);
	}

	// compare two Angle
	// if two Angle have different start Vector, give assertion failed, otherwise
	// if this Angle is bigger than input Angle, return 1
	// if this Angle is smaller than input Angle, return -1
	// if two Angle are exactly same, return 0
	inline int compare(const Angle& input) {
		assert(start == input.start);
		return (end == input.end) ? 0 : (toRad() > input.toRad()) ? 1 : -1;
	}
};

#endif // !_ANGLE_H_
