#ifndef _GAME_H_
#define _GAME_H_

class Game {
protected:
	struct PieceState {
		size_t id;
		size_t state_count;
		Piece state[8];
	};
	struct PieceData {
		// Piece data ==========
		size_t piece_count;
		PieceState* piece;

	};
	// Board data ==========
	size_t board_id;
	Board board;

	PieceData game;

protected:
	bool readFile(const char* filename) {
		static const size_t MAX_COUNT = 32;
		Point point[MAX_COUNT];

		FILE *fin = fopen(filename, "rb");
		if (fin == NULL) {
			printf("Unable to open file.\n");
			return false;
		}

		// read Piece ==========
		fscanf(fin, "%u", &game.piece_count);
		game.piece = memalloc<PieceState>(game.piece_count);
		for (size_t i = 0; i < game.piece_count; i += 1) {
			size_t piece_id, point_count;

			fscanf(fin, "%u%u", &piece_id, &point_count);
			game.piece[i].id = piece_id;
			game.piece[i].state_count = 1;

			for (size_t j = 0; j < point_count; j += 1) {
				size_t x, y;
				fscanf(fin, "%u%u", &x, &y);
				point[j] = Point(x, y);
			}
			game.piece[i].state[0] = Piece(point, point_count);
		}

		// read Board ==========
		size_t point_count;
		fscanf(fin, "%u%u", &board_id, &point_count);
		for (size_t j = 0; j < point_count; j += 1) {
			size_t x, y;
			fscanf(fin, "%u%u", &x, &y);
			point[j] = Point(x, y);
		}
		Piece piece = Piece(point, point_count);
		Vector vector = Vector(0, 0);
		board = Board(&piece, &vector, 1);

		fclose(fin);
		return true;
	}

public:
	Game() {}
	~Game() {}

	bool startup() {
		if (readFile("input_1.txt") == false) {
			return false;
		}
		//rotatePiece(game.piece, game.piece_count);
	}

	bool run() {
		// TODO: implement this @thanhminhmr
	}

    //Put in public for testing purpose
    static void rotatePiece(PieceState* piece, size_t piece_count);
    static PieceState generateStates(const Piece& initState);
    static Piece generateNextRotation(const Piece& piece);
    static Piece generateFlip(const Piece& piece_in);
};

//Flip the piece
Piece Game::generateFlip(const Piece& piece_in) {
    size_t piece_size = piece_in.size;
    Point newPoints[piece_size];
    for (int i = 0; i < piece_size; i++) {
        int x = 101 - 1 - piece_in.points[i].x;
        int y = piece_in.points[i].y; //width - 1 - piece.points[i].x -> width = 65 or 100 ?
        newPoints[i] = Point(x, y);
    }
  //  printf("%u", newPoints[piece_size].x);
    return Piece(newPoints, piece_size); //
}

//Rotate the piece 90 degree counter-clockwise
Piece Game::generateNextRotation(const Piece& piece) {
    Point newPoints[piece.size];
    size_t piece_size = piece.size;
    for (int i = 0; i < piece_size; i++) {
        int x = piece.points[i].y;
        int y = 101 - 1 - piece.points[i].x; //width - 1 - piece.points[i].x -> width = 65 or 100 ?
        newPoints[i] = Point(x, y);
    }
    return Piece(newPoints, piece_size);
}

Game::PieceState Game::generateStates(const Piece& initState) {
    PieceState pieceState;
    //generate rotation of initPiece
    pieceState.state[0] = initState;
    for (int i = 1; i < 4; i++) {
        pieceState.state[i] = generateNextRotation(state[i - 1]);
    }
    //generate rotation of flipped piece
    pieceState.state[4] = generateFlip(initState);
    for (int i = 5; i < 8; i++) {
        pieceState.state[i] = generateNextRotation(state[i - 1]);
    }
    pieceState.state_count = 8; // Decrement later if isIndentify()???
    return pieceState;
}

void Game::rotatePiece(PieceState* piece, size_t piece_count) {
	// TODO: implement this
    for (int i = 0; i < piece_count; i++) {
        piece[i] = generateStates(piece[i].state[0]);
    }
}

#endif // !_GAME_H_
