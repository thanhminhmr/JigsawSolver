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
	inline Board subtract(size_t index, Piece piece, const Vector& position) const;

	inline Board subtract(Piece pa, Piece pb);

    inline Board converseFromGPCPolygon(gpc_polygon p);
};

//Converse from GPC's polygon into pieces
inline Board Board::converseFromGPCPolygon(gpc_polygon p) {
    int piece_count = p.num_contours;
    Piece pieces[piece_count];
    for (int i = 0; i < piece_count; i++) {
        int piece_size = p.contour[i].num_vertices;
        Point points[piece_size];
        for (int v = 0; v < piece_size; v++) {
            points[v] = Point(p.contour[i].vertex[v].x, p.contour[i].vertex[v].y);
        }
        pieces[i] = Piece(points, piece_size);
    }

    return Board(pieces, piece_count);
}

inline Board Board::subtract(Piece pa, Piece pb) {
    gpc_polygon polygon_a = pa.converseToGpcPolygon();
    gpc_polygon polygon_b = pb.converseToGpcPolygon();
    gpc_polygon result;
    gpc_polygon_clip(GPC_DIFF, &polygon_a, &polygon_b, &result);
    return converseFromGPCPolygon(result);
}
// subtract Piece from Board, return new Board
inline Board Board::subtract(size_t index, Piece piece, const Vector& position) const {
	assert(index < size);
	// TODO: implement this
	Board resBoard;
	Piece resPieces[size + 5];

	size_t c = 0; //count number of pieces in new Board

	Piece p_a = pieces[index];
    Piece p_b = piece.move(position);
    Board clippedBoard = clippedBoard.subtract(p_a, p_b); //A sub board after subtract 2 pieces

    for (size_t i = 0; i < size; i++) {
        if (index == i) { //If is index th, subtract Board
            for (size_t j = 0; j < clippedBoard.size; j++) {
                resPieces[c] = clippedBoard.pieces[j];
                c ++;
            }
        } else { //else, leave alone
            resPieces[c] = pieces[i];
            c ++;
        }
    }

    resBoard = Board(resPieces, c);
    return resBoard;
}
#endif // !_BOARD_H_
