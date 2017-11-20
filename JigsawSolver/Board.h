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
	Vector const * const positions;
	const size_t size;

	// default destructor
	inline ~Board() {
		memdealloc(pieces);
	}
	// default constructor
	inline Board() : pieces(NULL), positions(NULL), size(0) {}
	// constructor
	inline Board(const Piece* pieces, const Vector* positions, size_t size)
		: pieces(memalloc<Piece>(size)), positions(memalloc<Vector>(size)), size(size) {

		memcopy((Piece*) this->pieces, pieces, size);
		memcopy((Vector*) this->positions, positions, size);
	}
	// copy constructor
	inline Board(const Board& board)
		: pieces(memalloc<Piece>(board.size)), positions(memalloc<Vector>(board.size)), size(board.size) {

		memcopy((Piece*) pieces, board.pieces, size);
		memcopy((Vector*) positions, board.positions, size);
	}
	// copy operator
	inline void operator=(const Board& board) {
		this->~Board();
		new(this) Board(board);
	}

	// subtract Piece from Board, return new Board
	inline Board subtract(size_t index, const Piece& piece, const Vector& place);
};

// subtract Piece from Board, return new Board
inline Board Board::subtract(size_t index, const Piece& piece, const Vector& position) {
	assert(index < size);
	// TODO: implement this
	return Board();
}
#endif // !_BOARD_H_
