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
	Point* point;
	Angle* angle;

	// normalize this Piece
	static inline void normalize(Point* point_out, const Point* point_in, size_t size);

public:
	const size_t size;

	// default destructor
	inline ~Piece() {
		memdealloc(point);
	}
	// default constructor
	inline Piece() : point(NULL), angle(NULL), size(0) {}
	// constructor
	inline Piece(const Point* _point, size_t _size) : point(NULL), angle(NULL), size(_size) {
		point = memalloc<Point>(size);
		normalize(point, _point, size);
	}
	// copy constructor
	inline Piece(const Piece& piece) : point(NULL), angle(NULL), size(piece.size) {
		point = memalloc<Point>(size);
		memcopy(point, piece.point, size);
	}
	// copy operator
	inline void operator=(const Piece& piece) {
		this->~Piece();
		new(this) Piece(piece);
	}
};

// normalize this Piece
inline void Piece::normalize(Point* point_out, const Point* point_in, size_t size) {
	// TODO: do we need this?
}
#endif // !_PIECE_H_
