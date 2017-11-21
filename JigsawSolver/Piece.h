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
	static inline Vector normalizePosition(Point* point_out, const Point* point_in, size_t size);

	// create Angle array from normalized Point array
	static inline void createAngle(Angle* angle, const Point* point, size_t size);

	// check if two Piece (Point array) is identical
	static inline bool isIdentical(const Point* points_a, const Point* points_b, size_t size);

	// check if Piece a (Point array) can contain Piece b (Point array)
	static inline bool isContainable(const Point* points_a, const Point* points_b, size_t size, const Vector& position);

protected:
	// constructor, normalize Piece position
	inline Piece(const Piece& piece, Vector& position)
		: points(memalloc<Point>(piece.size)), angles(memalloc<Angle>(piece.size)), size(piece.size) {

		position = normalizePosition((Point*) points, piece.points, size);
		memcopy((Angle*) angles, piece.angles, size);
	}

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
	// constructor
	inline Piece(const Point* points, size_t size)
		: points(memalloc<Point>(size)), angles(memalloc<Angle>(size)), size(size) {
		assert(size >= 3);

		normalizeClockwise((Point*) this->points, points, size);
		createAngle((Angle*) angles, points, size);
	}
	// copy constructor
	inline Piece(const Piece& piece)
		: points(memalloc<Point>(piece.size)), angles(memalloc<Angle>(piece.size)), size(piece.size) {

		memcopy((Point*) points, piece.points, size);
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

	// normalize this Piece position, return new Piece and position
	inline Piece normalize(Vector& position) const {
		return Piece(*this, position);
	}

	// normalize this Piece position, return new Piece
	inline Piece normalize() const {
		Vector position;
		return Piece(*this, position);
	}

	// check if Piece a (Point array) can contain Piece b (Point array)
	inline bool isContainable(const Piece& piece, const Vector& position) const {
		return isContainable(points, piece.points, size, position);
	}
};

// normalize this Piece to clockwise list of Point
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

// normalize this Piece position
inline Vector Piece::normalizePosition(Point* point_out, const Point* point_in, size_t size) {
	int16_t left = point_in[0].x;
	int16_t top = point_in[0].y;
	for (size_t i = 0; i < size; i++) {
		// if (highest < point_out[i].y) highest = point_out[i].y;
		top = (top < point_in[i].y) ? point_in[i].y : top;
		// if (left < point_out[i].x) left = point_out[i].x;
		left = (left < point_in[i].x) ? point_in[i].x : left;
	}
	Vector delta(-left, -top);
	for (size_t i = 0; i < size; i++) {
		point_out[i] = delta.move(point_in[i]);
	}
	return Vector(left, top);
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

// check if Piece a (Point array) can contain Piece b (Point array)
inline bool Piece::isContainable(const Point* points_a, const Point* points_b, size_t size, const Vector& position) {
	// TODO: implement this
	return false;
}

#endif // !_PIECE_H_
