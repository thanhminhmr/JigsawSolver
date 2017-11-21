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

	// subtract Piece from Board, return new Board
	inline Board subtract(size_t index, const Piece& piece, const Vector& position) const;
};

// subtract Piece from Board, return new Board
inline Board Board::subtract(size_t index, const Piece& piece, const Vector& position) const {
	assert(index < size);
	// TODO: implement this
	return Board();
}
#endif // !_BOARD_H_
