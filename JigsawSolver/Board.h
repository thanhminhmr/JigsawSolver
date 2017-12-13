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
	PieceReference const * const piecerefs;
	const size_t refsize;

	// default destructor
	inline ~Board() {
		memdealloc(pieces);
		memdealloc(piecerefs);
	}
	// default constructor
	inline Board() : pieces(NULL), size(0), piecerefs(NULL), refsize(0) {}
	// constructor
	inline Board(const Piece* pieces, size_t size)
		: pieces(memalloc<Piece>(size)), size(size), piecerefs(NULL), refsize(0) {

		memcopy((Piece*) this->pieces, pieces, size);
	}
	// constructor
	inline Board(const Piece* pieces, size_t size, const PieceReference* piecerefs, size_t refsize)
		: pieces(memalloc<Piece>(size)), size(size),
		piecerefs(memalloc<PieceReference>(refsize)), refsize(refsize) {

		memcopy((Piece*) this->pieces, pieces, size);
		memcopy((PieceReference*) this->piecerefs, piecerefs, refsize);
	}
	// copy constructor
	inline Board(const Board& board)
		: pieces(memalloc<Piece>(board.size)), size(board.size),
		piecerefs(memalloc<PieceReference>(board.refsize)), refsize(board.refsize) {

		memcopy((Piece*) pieces, board.pieces, size);
		memcopy((PieceReference*) this->piecerefs, piecerefs, refsize);
	}
	// copy operator
	inline void operator=(const Board& board) {
		this->~Board();
		new(this) Board(board);
	}

protected:
	// subtract two Piece, return number of new Piece created, write to array of Piece
	static inline size_t subtract(Piece* pieces_out,
		const Point* big_piece_points, size_t big_piece_size, size_t big_piece_index,
		const Point* small_piece_points, size_t small_piece_size, size_t small_piece_index);

public:
	// subtract Piece from Board, return new Board
	inline Board subtract(bool piece_from_ref, size_t board_piece_index, size_t board_point_index, 
		const Piece& piece, size_t piece_point_index, const Vector& position) const;
};

// subtract Piece from Board, return new Board
inline Board Board::subtract(bool piece_from_ref, size_t board_piece_index, size_t board_point_index, 
	const Piece& piece, size_t piece_point_index, const Vector& position) const {
	assert(board_piece_index < size);
	assert(board_point_index < MAX_POINT_COUNT);
	// small Piece is here
	Point small_piece_points[MAX_POINT_COUNT];
	for (size_t i = 0; i < piece.size; i++) {
		small_piece_points[i] = position.move(piece.points[i]);
	}
	// do things and put new Piece(s) here
	Piece pieces_out[MAX_PIECE_COUNT];
	size_t size_out = subtract(pieces_out,
		pieces[board_piece_index].points, pieces[board_piece_index].size, board_point_index,
		small_piece_points, piece.size, piece_point_index);
	// put PieceReference and return here
	PieceReference piecerefs_out[MAX_PIECEREF_COUNT];
	size_t refsize_out = 0;
	if (piece_from_ref) {
		// convert all Piece to PieceReference
		for (size_t i = 0; i < size; i++) {
			piecerefs_out[refsize_out] = &pieces[i];
			refsize_out += 1;
		}
		// copy leftover PieceReference
		for (size_t i = 0; i < refsize; i++) {
			if (i != board_piece_index) {
				piecerefs_out[refsize_out] = piecerefs[i];
				refsize_out += 1;
			}
		}
	} else {
		// convert all Piece to PieceReference
		for (size_t i = 0; i < size; i++) {
			if (i != board_piece_index) {
				piecerefs_out[refsize_out] = &pieces[i];
				refsize_out += 1;
			}
		}
		// copy leftover PieceReference
		for (size_t i = 0; i < refsize; i++) {
			piecerefs_out[refsize_out] = piecerefs[i];
			refsize_out += 1;
		}
	}
	return Board(pieces_out, size_out, piecerefs_out, refsize_out);
}

// subtract two Piece, return number of new Piece created, write to array of Piece
inline size_t Board::subtract(Piece* pieces_out,
	const Point* big_piece_points, size_t big_piece_size, size_t big_piece_index,
	const Point* small_piece_points, size_t small_piece_size, size_t small_piece_index) {
	// TODO: implement this
}

#endif // !_BOARD_H_
