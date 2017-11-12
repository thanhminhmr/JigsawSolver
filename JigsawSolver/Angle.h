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
	// constructor, Angle from 3 Point
	inline Angle(const Point& prev, const Point& current, const Point& next)
		: start(Vector(current, next).normalize()), end(Vector(current, prev).normalize()) {}
	// constructor, Angle from 2 Vector
	inline Angle(const Vector& a, const Vector& b) : start(a.normalize()), end(b.normalize()) {}
	// copy constructor
	inline Angle(const Angle& angle) : start(angle.start), end(angle.end) {}
	// copy operator
	inline void operator=(const Angle& angle) {
		this->~Angle();
		new(this) Angle(angle);
	}

	// misc, compare two Angle
	inline bool operator==(const Angle& angle) const {
		return start == angle.start && end == angle.end;
	}
	// misc, compare two Angle
	inline bool operator!=(const Angle& angle) const {
		return start != angle.start || end != angle.end;
	}

	// get the angle between [0, 2 * pi) radians
	inline float toRad() const {
		// dot product between[x1, y1] and [x2, y2]
		int32_t dot = (int32_t) start.x * (int32_t) end.x + (int32_t) start.y * (int32_t) end.y;
		// determinant
		int32_t det = (int32_t) start.x * (int32_t) end.y - (int32_t) start.y * (int32_t) end.x;
		// atan2(y, x) or atan2(sin, cos)
		float angle = atan2f((float) det, (float) dot);
		// convert [-pi, +pi] to [0, 2 * pi)
		return (angle >= 0.0f) ? angle : (2.0f * M_PI - angle);
	}
};

#endif // !_ANGLE_H_
