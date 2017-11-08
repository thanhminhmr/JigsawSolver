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
	// normalize this Piece
	static inline void normalize(Point* point_out, const Point* point_in, size_t size);

	// create Angle array from normalized Point array
	static inline void createAngle(Angle* angle, const Point* point, size_t size);

public:
	Point const * const point;
	Angle const * const angle;
	const size_t size;

	// default destructor
	inline ~Piece() {
		memdealloc(point);
		memdealloc(angle);
	}
	// default constructor
	inline Piece() : point(NULL), angle(NULL), size(0) {}
	// constructor
	inline Piece(const Point* _point, size_t _size)
		: point(memalloc<Point>(_size)), angle(memalloc<Angle>(_size)), size(_size) {

		normalize((Point*) point, _point, size);
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
};

// normalize this Piece
inline void Piece::normalize(Point* point_out, const Point* point_in, size_t size) {
	// TODO: do we need this?
}

// create Angle array from normalized Point array
inline void Piece::createAngle(Angle * angle, const Point * point, size_t size) {
	// TODO: implement this
}

#endif // !_PIECE_H_
