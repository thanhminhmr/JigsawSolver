#ifndef _BOARD_H_
#define _BOARD_H_

/**
* Board.h
*
* Define a Board
*
* ! initialize on create
* ! read - only
*/
class Board {
public:
	Piece const * const pieces;
	const size_t size;

	// default destructor
	inline ~Board() {
		memdealloc(pieces);
	}
	// default constructor
	inline Board() : pieces(NULL), size(0) {}
	// constructor
	inline Board(const Piece* pieces, size_t size)
		: pieces(memalloc<Piece>(size)), size(size) {

		memcopy((Piece*) this->pieces, pieces, size);
	}
	// copy constructor
	inline Board(const Board& board)
		: pieces(memalloc<Piece>(board.size)), size(board.size) {

		memcopy((Piece*) pieces, board.pieces, size);
	}
	// copy operator
	inline void operator=(const Board& board) {
		this->~Board();
		new(this) Board(board);
	}

protected:
	// subtract two Piece, return number of new Piece created, write to array of Piece
	inline size_t subtract(Piece* pieces_out,
		const Point* big_piece_points, size_t big_piece_size, size_t big_piece_index,
		const Point* small_piece_points, size_t small_piece_size, size_t small_piece_index);

public:
	// subtract Piece from Board, return new Board
	inline Board subtract(size_t index, const Piece& piece, const Vector& position) const;
};

// subtract Piece from Board, return new Board
inline Board Board::subtract(size_t index, const Piece& piece, const Vector& position) const {
	assert(index < size);
	// TODO: implement this
	return Board();
}

// subtract two Piece, return number of new Piece created, write to array of Piece
inline size_t Board::subtract(Piece* pieces_out,
	const Point* big_piece_points, size_t big_piece_size, size_t big_piece_index,
	const Point* small_piece_points, size_t small_piece_size, size_t small_piece_index) {
	// TODO: implement this
}

#endif // !_BOARD_H_
