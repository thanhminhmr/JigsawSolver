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
class Board : public Piece {
	//static const size_t MAX_SIZE = 128;
private:
	// copy constructor
	inline Board(const Board& Board) {}

public:
	// default constructor
	inline Board() : Piece() {}

	// constructor
	inline Board(const Point* _point, size_t _size) : Piece(_point, _size) {}

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
