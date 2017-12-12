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
		Point point[MAX_POINT_COUNT];

		FILE *fin = fopen(filename, "rb");
		if (fin == NULL) {
			printf("Unable to open file.\n");
			return false;
		}

		// read Piece ==========
		fscanf(fin, "%zu", &game.piece_count);
		game.piece = memalloc<PieceState>(game.piece_count);
		for (size_t i = 0; i < game.piece_count; i += 1) {
			size_t piece_id, point_count;

			fscanf(fin, "%zu%zu", &piece_id, &point_count);
			game.piece[i].id = piece_id;
			game.piece[i].state_count = 1;

			for (size_t j = 0; j < point_count; j += 1) {
				size_t x, y;
				fscanf(fin, "%zu%zu", &x, &y);
				point[j] = Point(x, y);
			}
			game.piece[i].state[0] = Piece(point, point_count);
		}

		// read Board ==========
		size_t point_count;
		fscanf(fin, "%zu%zu", &board_id, &point_count);
		for (size_t j = 0; j < point_count; j += 1) {
			size_t x, y;
			fscanf(fin, "%zu%zu", &x, &y);
			point[j] = Point(x, y);
		}
		Piece piece(point, point_count, false);
		board = Board(&piece, 1);

		fclose(fin);
		return true;
	}

	static void rotatePiece(PieceState& piece);

public:
	Game() {}
	~Game() {}

	bool startup() {
		if (readFile("input_1.txt") == false) {
			return false;
		}
		for (size_t piece_index = 0; piece_index < game.piece_count; piece_index++) {
			rotatePiece(game.piece[piece_index]);
		}
	}

	void run() {
		// TODO: implement this @thanhminhmr
	}
};

void Game::rotatePiece(PieceState& piece) {
	// TODO: implement this
}

#endif // !_GAME_H_
