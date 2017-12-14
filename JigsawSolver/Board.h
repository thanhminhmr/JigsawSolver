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
	// find line segment of Piece that contain Point
	static inline size_t findIntersectSegment(const Point* points, size_t size, const Point& point);

	// create new Piece with intersect another Point from another Piece
	static inline size_t createIntersectPoints(Point* intersect_points, const Point* points_a, size_t size_a,
		const Point* points_b, size_t size_b, const size_t* mask_b);

public:
	// subtract Piece from Board, return new Board
	inline Board subtract(bool piece_from_ref, size_t board_piece_index, size_t board_point_index,
		const Piece& piece, size_t piece_point_index, const Vector& position) const;
};

// find line segment of Piece that contain Point
inline size_t Board::findIntersectSegment(const Point* points, size_t size, const Point& point) {
	if (points[size - 1] == point || points[0] == point) {
		// vertex
	} else if (Point::isOnSegment(points[size - 1], points[0], point)) {
		return size - 1;
	} else {
		for (size_t index = 0; index < size - 1; index++) {
			// check if point is on line segment points[index, index + 1]
			if (points[index] == point || points[index + 1] == point) {
				// vertex
				break;
			} else if (Point::isOnSegment(points[index], points[index + 1], point)) {
				return index;
			}
		}
	}
	// not found
	return size;
}

// create new Piece with intersect another Point from another Piece
inline size_t Board::createIntersectPoints(Point* intersect_points, const Point* points_a, size_t size_a,
	const Point* points_b, size_t size_b, const size_t* mask_b) {
	size_t intersect_size = 0;
	size_t index_a = 0;
	size_t index_b = 0;
	do {
		if (mask_b[index_b] < size_b) {
			while (index_a <= mask_b[index_b]) {
				intersect_points[intersect_size] = points_a[index_a];
				intersect_size += 1;
				index_a += 1;
			};
			intersect_points[intersect_size] = points_b[index_b];
			intersect_size += 1;
		}
		index_b += 1;
	} while (index_b < size_b);
	while (index_a < size_a) {
		intersect_points[intersect_size] = points_a[index_a];
		intersect_size += 1;
		index_a += 1;
	};
	intersect_points[intersect_size] = points_a[0];
	return intersect_size;
}

// subtract Piece from Board, return new Board
inline Board Board::subtract(bool piece_from_ref, size_t board_piece_index, size_t board_point_index,
	const Piece& piece, size_t piece_point_index, const Vector& position) const {
	assert(board_piece_index < size);
	assert(board_point_index < MAX_POINT_COUNT);

	// ===== Create Point Array
	const Piece& big_piece = piece_from_ref ? *piecerefs[board_piece_index] : pieces[board_piece_index];
	Point big_points[MAX_POINT_COUNT];
	Point small_points[MAX_POINT_COUNT];
	size_t big_size = 0;
	size_t small_size = 0;
	// big Piece is here
	for (size_t i = board_point_index + 1; i < big_piece.size; i++) {
		big_points[big_size] = big_piece.points[i];
		big_size += 1;
	}
	for (size_t i = 0; i <= board_point_index; i++) {
		big_points[big_size] = big_piece.points[i];
		big_size += 1;
	}
	// small Piece is here
	for (size_t i = piece_point_index + 1; i < piece.size; i++) {
		small_points[small_size] = position.move(piece.points[i]);
		small_size += 1;
	}
	for (size_t i = 0; i <= piece_point_index; i++) {
		small_points[small_size] = position.move(piece.points[i]);
		small_size += 1;
	}

	// ===== Create Intersect Mask Array
	size_t big_mask[MAX_POINT_COUNT];
	size_t small_mask[MAX_POINT_COUNT];
	// big mask array, mask if Point of big_piece on small_piece line segment
	for (size_t big_index = 0; big_index < big_size; big_index++) {
		big_mask[big_index] = findIntersectSegment(small_points, small_size, big_points[big_index]);
	}
	// small mask array, mask if Point of small_piece on big_piece line segment
	for (size_t small_index = 0; small_index < small_size; small_index++) {
		small_mask[small_index] = findIntersectSegment(big_points, big_size, small_points[small_index]);
	}

	// ===== Create Intersect Points
	Point big_intersect_points[MAX_POINT_COUNT];
	Point small_intersect_points[MAX_POINT_COUNT];
	size_t big_intersect_size =
		createIntersectPoints(big_intersect_points, big_points, big_size,
			small_points, small_size, small_mask);
	size_t small_intersect_size =
		createIntersectPoints(small_intersect_points, small_points, small_size,
			big_points, big_size, big_mask);

	// ===== Fight!
	Piece pieces_out[MAX_PIECE_COUNT];
	size_t size_out = 0;

	size_t big_index = 0;
	size_t small_index = 0;
	do {
		// skip perfect match
		while (big_index < big_intersect_size &&  big_intersect_points[big_index + 1] == small_intersect_points[small_index + 1]) {
			big_index += 1;
			small_index += 1;
		}
		if (big_index == big_intersect_size) {
			// done
			break;
		}
		// create new piece
		Point points_out[MAX_POINT_COUNT];
		size_t point_size_out = 0;
		size_t big_end = 0;
		do {
			points_out[point_size_out] = small_intersect_points[small_index];
			point_size_out += 1;
			small_index += 1;
			for (size_t big_scan = big_index + 1; big_scan <= big_intersect_size; big_scan++) {
				if (small_intersect_points[small_index] == big_intersect_points[big_scan]) {
					big_end = big_scan;
					break;
				}
			}
		} while (big_end == 0);
		for (size_t big_scan = big_end; big_scan > big_index; big_scan--) {
			points_out[point_size_out] = big_intersect_points[big_scan];
			point_size_out += 1;
		}
		big_index = big_end;

		pieces_out[size_out] = Piece(points_out, point_size_out);
		size_out += 1;
	} while (true);

	// ===== put PieceReference and return here
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

#endif // !_BOARD_H_
