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
	Piece const * const piece;
	const size_t size;

	// default destructor
	inline ~Board() {
		memdealloc(piece);
	}
	// default constructor
	inline Board() : piece(NULL), size(0) {}
	// constructor
	inline Board(const Piece* piece, size_t size)
		: piece(memalloc<Piece>(size)), size(size) {

		memcopy((Piece*) this->piece, piece, size);
	}
	// copy constructor
	inline Board(const Board& board)
		: piece(memalloc<Piece>(board.size)), size(board.size) {

		memcopy((Piece*) piece, board.piece, size);
	}
	// copy operator
	inline void operator=(const Board& board) {
		this->~Board();
		new(this) Board(board);
	}

	// subtract Piece from Board, return new Board
	inline Board subtract(size_t index, const Piece& piece);
};

// subtract Piece from Board, return new Board
inline Board Board::subtract(size_t index, const Piece & piece) {
	// TODO: implement this
	return Board();
}
#endif // !_BOARD_H_
