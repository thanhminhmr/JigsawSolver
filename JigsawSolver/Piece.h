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

	// allocate
	template<class Type>
	static inline Point* _alloc(size_t size) {
		// TODO: aligned alloc @thanhminhmr
		return new Type[size];
	}
	// deallocate
	template<class Type>
	static inline void _dealloc(Type* type) {
		// TODO: aligned dealloc @thanhminhmr
		delete[] type;
	}

	// normalize this Piece
	static inline void normalize(Point* point_out, const Point* point_in, size_t size);

public:
	const size_t size;

	// default destructor
	inline ~Piece() {
		_dealloc(point);
	}

	// default constructor
	inline Piece() : point(NULL), angle(NULL), size(0) {}

	// constructor
	inline Piece(const Point* _point, size_t _size) : point(NULL), angle(NULL), size(_size) {
		point = _alloc<Point>(size);
		normalize(point, _point, size);
	}

	// copy constructor
	inline Piece(const Piece& piece) : point(NULL), angle(NULL), size(piece.size) {
		point = _alloc<Point>(size);
		memcopy(point, piece.point, size);
	}
};

// normalize this Piece
inline void Piece::normalize(Point* point_out, const Point* point_in, size_t size) {
	// TODO: implement this
}
#endif // !_PIECE_H_
