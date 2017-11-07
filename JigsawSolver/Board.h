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
private:
	static const size_t MAX_SIZE = 16;

protected:
	Piece piece[MAX_SIZE];

public:
	// default constructor
	inline Board() {}

	// constructor
	inline Board(const Piece* _point, size_t _size) {
		// TODO: implement this @thanhminhmr
	}

	// Subtract this Board with a Board into new Board
	inline Board subtract(const Board& Board) const {
		// TODO: implement this
	}

	// Merge two Board into new Board
	inline Board merge(const Board& Board) const {
		// TODO: do we need this?
	}
};

#endif // !_BOARD_H_
