#ifndef _PIECE_H_
#define _PIECE_H_

/**
* Piece.h
*
* Define a Piece
*
* ! initialize on create
* ! read - only
*/
class Piece {
protected:
	// normalize this Piece to clockwise list of Point
	static inline void normalizeClockwise(Point* point_out, const Point* point_in, size_t size);

	// normalize this Piece position
	static inline void normalizePosition(Point* point_out, const Point* point_in, size_t size);

	// create Angle array from normalized Point array
	static inline void createAngle(Angle* angle, const Point* point, size_t size);

	// check if two Piece (Point array) is identical
	static inline bool isIdentical(const Point* points_a, const Point* points_b, size_t size);

private:
	// Count if line segment AB and ray Cx intersect, return true if C is between A and B
	static inline bool isOnSegmentAndCountIntersect(const Point& a, const Point& b, const Point& c, size_t& intersect_count);

	// Check if point inside the piece
	static inline bool isPointInside(const Point* points, size_t size, const Point& point);

protected:
	// check if Piece a (Point array) can contain Piece b (Point array)
	static inline bool isContainable(const Point* points_a, size_t size_a, const Point* points_b, size_t size_b, const Vector& position);

public:
	Point const * const points;
	Angle const * const angles;
	const size_t size;

	// default destructor
	inline ~Piece() {
		memdealloc(points);
		memdealloc(angles);
	}
	// default constructor
	inline Piece() : points(NULL), angles(NULL), size(0) {}

	// constructor, can normalize Piece position
	inline Piece(const Point* points, size_t size, bool normalizing = true)
		: points(memalloc<Point>(size)), angles(memalloc<Angle>(size)), size(size) {
		assert(size >= 3);

		normalizeClockwise((Point*) this->points, points, size);
		if (normalizing) {
			normalizePosition((Point*) this->points, (Point*) this->points, size);
		}
		createAngle((Angle*) angles, points, size);
	}
	// copy constructor, can normalize Piece position
	inline Piece(const Piece& piece, bool normalizing = true)
		: points(memalloc<Point>(piece.size)), angles(memalloc<Angle>(piece.size)), size(piece.size) {
		if (normalizing) {
			normalizePosition((Point*) points, piece.points, size);
		} else {
			memcopy((Point*) points, piece.points, size);
		}
		memcopy((Angle*) angles, piece.angles, size);
	}
	// copy operator
	inline void operator=(const Piece& piece) {
		this->~Piece();
		new(this) Piece(piece);
	}

	// misc, compare two Piece
	inline bool operator==(const Piece& piece) const {
		return isIdentical(points, piece.points, size);
	}
	// misc, compare two Piece
	inline bool operator!=(const Piece& piece) const {
		return isIdentical(points, piece.points, size) == false;
	}

	// check if Piece a can contain Piece b
	inline bool isContainable(const Piece& piece, const Vector& position) const {
		return isContainable(points, size, piece.points, piece.size, position);
	}

	// normalize this Piece position, return new Piece
	inline Piece normalize() const {
		return Piece(*this);
	}

	// Flip this piece
	inline Piece flip() const {
		Point points_out[MAX_POINT_COUNT];
		for (size_t i = 0; i < size; i++) {
			points_out[i] = Point(-points[i].x, points[i].y);
		}
		return Piece(points_out, size);
	}

	// Rotate the piece 90 degree counter-clockwise
	inline Piece rotate() const {
		Point points_out[MAX_POINT_COUNT];
		for (size_t i = 0; i < size; i++) {
			points_out[i] = Point(points[i].y, -points[i].x);
		}
		return Piece(points_out, size);
	}

	// move
	inline Piece move(const Vector& position) const {
		Point points_out[MAX_POINT_COUNT];
		for (size_t i = 0; i < size; i++) {
			points_out[i] = position.move(points[i]);
		}
		return Piece(points_out, size, false);
	}
};

typedef const Piece* PieceReference;

// normalize this Piece to clockwise list of Point (in_place safe)
inline void Piece::normalizeClockwise(Point* point_out, const Point* point_in, size_t size) {
	int32_t sum = ((int32_t) point_in[0].x - (int32_t) point_in[size - 1].x)
		* ((int32_t) point_in[0].y + (int32_t) point_in[size - 1].y);

	for (size_t i = 1; i < size; i++) {
		sum += ((int32_t) point_in[i].x - (int32_t) point_in[i - 1].x)
			* ((int32_t) point_in[i].y + (int32_t) point_in[i - 1].y);
	}
	if (sum > 0) {
		memcopy(point_out, point_in, size);
	} else if (sum < 0) {
		for (size_t i = 0, j = size - 1; i < size; i++, j--) {
			point_out[i] = point_in[j];
		}
	}
}

// normalize this Piece position (in_place safe)
inline void Piece::normalizePosition(Point* point_out, const Point* point_in, size_t size) {
	int16_t left = point_in[0].x;
	int16_t top = point_in[0].y;
	for (size_t i = 0; i < size; i++) {
		top = (top > point_in[i].y) ? point_in[i].y : top;
		left = (left > point_in[i].x) ? point_in[i].x : left;
	}
	Vector delta(-left, -top);
	for (size_t i = 0; i < size; i++) {
		point_out[i] = delta.move(point_in[i]);
	}
}

// create Angle array from normalized Point array
inline void Piece::createAngle(Angle* angles, const Point* points, size_t size) {
	angles[0] = Angle(points[size - 1], points[0], points[1]);
	for (size_t i = 2; i < size; i++) {
		angles[i] = Angle(points[i - 2], points[i - 1], points[i]);
	}
	angles[size - 1] = Angle(points[size - 2], points[size - 1], points[0]);
}

// check if two Piece is identical
inline bool Piece::isIdentical(const Point* points_a, const Point* points_b, size_t size) {
	for (size_t delta = 0; delta < size; delta++) {
		if (points_a[0] == points_b[delta]) {
			for (size_t i = 0; i < size; i++) {
				if (points_a[i] != points_b[(i + delta) % size]) {
					return false;
				}
			}
			return true;
		}
	}
	return false;
}

// Count if line segment AB and ray Cx intersect, return true if C is between A and B
inline bool Piece::isOnSegmentAndCountIntersect(const Point& a, const Point& b, const Point& c, size_t& intersect_count) {
	if (c.y < min(a.y, b.y) || c.y > max(a.y, b.y) || c.x > max(a.x, b.x)) {
		// Cx is above, below or on the right side of AB
	} else {
		// equation of line AB, test with C
		int tmp = (a.y - b.y) * (c.x - a.x) + (b.x - a.x) * (c.y - a.y);
		if ((tmp < 0 && (a.y > b.y)) || (tmp > 0 && (a.y < b.y))) {
			// Cx is on the left side of AB
			intersect_count += (c.y == a.y || c.y == b.y) ? 1 : 2;
		} else if (tmp == 0) {
			// Cx is on the same line with AB
			if (c.x < min(a.x, b.x)) {
				// Cx is on the left side of AB
				// in this case, we don't count an intersect
				return false;
			} else {
				// C is between A and B
				return true;
			}
		}
	}
	return false;
}

// Check if point inside the piece
inline bool Piece::isPointInside(const Point* points, size_t size, const Point& point) {
	assert(size >= 3);
	size_t count = 0; 
	if (isOnSegmentAndCountIntersect(points[size - 1], points[0], point, count)) {
		// on segment => inside piece
		return true;
	}
	for (size_t i = 1; i < size; i++) {
		if (isOnSegmentAndCountIntersect(points[i - 1], points[i], point, count)) {
			// on segment => inside piece
			return true;
		}
	}
	return (count & 2) != 0;
}

// check if Piece a (Point array) can contain Piece b (Point array)
inline bool Piece::isContainable(const Point* points_a, size_t size_a, const Point* points_b, size_t size_b, const Vector& position) {
	for (size_t i = 0; i < size_b; i++) {
		Point point = position.move(points_b[i]);
		if (isPointInside(points_a, size_a, point) == false) {
			return false;
		}
	}
	return true;
}

#endif // !_PIECE_H_
