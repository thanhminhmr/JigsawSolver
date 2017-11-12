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
	union {
		struct {
			const int16_t x, y;
		};
		const int32_t data;
	};

	// default constructor
	inline Vector() : x(0), y(0) {}
	// constructor
	inline Vector(int16_t x, int16_t y) : x(x), y(y) {}
	// constructor, create vector AB
	inline Vector(Point a, Point b) : x(b.x - a.x), y(b.y - a.y) {}
	// copy constructor
	inline Vector(const Vector& vector) : data(vector.data) {}
	// copy operator
	inline void operator=(const Vector& vector) {
		this->~Vector();
		new(this) Vector(vector);
	}

	inline void normalize() {
		this->~Vector();
		if (x != 0 && y != 0) {
			int32_t a = x, b = y;
			while (a != b) {
				*((a > b) ? (&a) : (&b)) -= *((a > b) ? (&b) : (&a));
			}
			new(this) Vector(x / a, y / a);
		} else if (x == 0) {
			new(this) Vector(0, (y >= 0) ? 1 : -1);
		} else {
			new(this) Vector((x >= 0) ? 1 : -1, 0);
		}
	}

	// move a Point with this Vector
	inline Point move(const Point& point) const {
		return Point(point.x + x, point.y + y);
	};

	// misc, compare two Vector
	inline bool operator==(const Vector& vector) const {
		return data == vector.data;
	}
	// misc, compare two Vector
	inline bool operator!=(const Vector& vector) const {
		return data != vector.data;
	}
};

#endif // !_VECTOR_H_
