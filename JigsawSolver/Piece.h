#ifndef _PIECE_H_
#define _PIECE_H_

/**
* Piece.h
*
* Define a Piece with maximum 126 Point (total size 512 bytes)
*
* ! read - write
* ! internal modify only
*/
// template <size_t MAX_SIZE>
class Piece {
	static const size_t MAX_SIZE = 128;
protected:
	Point* point;
	size_t size;

	// internal copy
	inline void copy(const Point* _point) {
		// TODO: aligned alloc @thanhminhmr
		point = new Point[MAX_SIZE];
		for (size_t i = 0; i < size; i++) {
			point[i] = _point[i];
		}
	}

	// normalize this Piece
	inline void normalize() {
		// TODO: implement this
	}

public:
	// default destructor
	inline ~Piece() {
		delete[] point;
	}

	// default constructor
	inline Piece() : point(NULL), size(0) {}

	// constructor
	inline Piece(const Point* _point, size_t _size) : point(NULL), size(_size) {
		assert(size <= MAX_SIZE);
		copy(_point);
	}

	// copy constructor
	inline Piece(const Piece&& piece) {
		size = piece.size;
		copy(piece.point);
	}

	// copy
	inline void operator=(const Piece& piece) {
		size = piece.size;
		copy(piece.point);
	}

	// Subtract this Piece with a Piece into new Piece
	inline Piece subtract(const Piece& piece) const {
		// TODO: implement this
	}

	// Merge two Piece into new Piece
	inline Piece merge(const Piece& piece) const {
		// TODO: do we need this?
	}
};

#endif // !_PIECE_H_
