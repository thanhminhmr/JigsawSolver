#ifndef _PIECE_H_
#define _PIECE_H_

/**
* Piece.h
*
* Define a Piece
*
* ! sized on create
* ! read - write
*/
class Piece {
protected:
	// normalize this Piece
	static inline void normalize(Point* point_out, const Point* point_in, size_t size);

	// create Angle array from normalized Point array
	static inline void createAngle(Angle* angle, const Point* point, size_t size);

	// check if two Piece (Point array) is identical
	static inline bool isIdentical(const Point* a, const Point* b, size_t size);

	// check if Piece a (Point array) can contain Piece b (Point array)
	static inline bool isContainable(const Point* a, const Point* b, size_t size);

public:
	Point const* const point;
	Angle const* const angle;
	const size_t size;

	// default destructor
	inline ~Piece() {
		memdealloc(point);
		memdealloc(angle);
	}
	// default constructor
	inline Piece() : point(NULL), angle(NULL), size(0) {}
	// constructor
	inline Piece(const Point* point, size_t size)
		: point(memalloc<Point>(size)), angle(memalloc<Angle>(size)), size(size) {

		normalize((Point*) this->point, point, size);
		createAngle((Angle*) angle, point, size);
	}
	// copy constructor
	inline Piece(const Piece& piece)
		: point(memalloc<Point>(piece.size)), angle(memalloc<Angle>(piece.size)), size(piece.size) {

		memcopy((Point*) point, piece.point, size);
		memcopy((Angle*) angle, piece.angle, size);
	}
	// copy operator
	inline void operator=(const Piece& piece) {
		this->~Piece();
		new(this) Piece(piece);
	}

	// misc, compare two Piece
	inline bool operator==(const Piece& piece) const {
		return isIdentical(point, piece.point, size);
	}
	// misc, compare two Piece
	inline bool operator!=(const Piece& piece) const {
		return isIdentical(point, piece.point, size) == false;
	}
};

// normalize this Piece
inline void Piece::normalize(Point* point_out, const Point* point_in, size_t size) {
	// TODO: implement this
}

// create Angle array from normalized Point array
inline void Piece::createAngle(Angle* angle, const Point* point, size_t size) {
	// TODO: implement this
}

// check if two Piece is identical
inline bool Piece::isIdentical(const Point* a, const Point* b, size_t size) {
	// TODO: implement this.
	return false;
}

// check if Piece a (Point array) can contain Piece b (Point array)
inline bool Piece::isContainable(const Point* a, const Point* b, size_t size) {
	// TODO: implement this
	return false;
}

#endif // !_PIECE_H_
