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
template <size_t MAX_SIZE>
class Piece {
	//static const size_t MAX_SIZE = 16;
private:
	// copy constructor
	inline Piece(const Piece& piece) {}

protected:
	Point* point;
	size_t size;

	// allocate
	static inline Point* _alloc(size_t size) {
		// TODO: aligned alloc @thanhminhmr
		return new Point[size];
	}

	// deallocate
	static inline void _dealloc(Point* point) {
		// TODO: aligned dealloc @thanhminhmr
		delete[] point;
	}

	// normalize this Piece
	static inline void normalize(Point* point_out, const Point* point_in, size_t size);

public:
	// default destructor
	inline ~Piece() {
		_dealloc(point);
	}

	// default constructor
	inline Piece() : point(NULL), size(0) {}

	// constructor
	inline Piece(const Point* _point, size_t _size) : point(NULL), size(_size) {
		assert(size <= MAX_SIZE);
		point = _alloc(MAX_SIZE);
		normalize(point, _point, size);
	}

	// copy
	inline void operator=(const Piece& piece) {
		size = piece.size;
		point = _alloc(MAX_SIZE);
		memcopy(point, piece.point, size);
	}
};

// normalize this Piece
template<size_t MAX_SIZE>
inline void Piece<MAX_SIZE>::normalize(Point * point_out, const Point * point_in, size_t size) {
	// TODO: implement this
}
#endif // !_PIECE_H_
