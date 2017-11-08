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
	inline Angle(const Point& prev, const Point& current, const Point& next) : start(current, next), end(current, prev) {}
	// constructor, Angle 
	inline Angle(const Vector& a, const Vector& b) : start(a), end(b) {}
	// copy constructor
	inline Angle(const Angle& angle) : start(angle.start), end(angle.end) {}
	// copy operator
	inline void operator=(const Angle& angle) {
		this->~Angle();
		new(this) Angle(angle);
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
};

#endif // !_ANGLE_H_
