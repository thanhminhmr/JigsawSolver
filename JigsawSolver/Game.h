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
			game.piece[i].state[0] = Piece(point, point_count).normalize();
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
		board = Board(&piece, 1);

		fclose(fin);
		return true;
	}

	static void rotatePiece(PieceState* piece, size_t piece_count);

public:
	Game() {}
	~Game() {}

	bool startup() {
		if (readFile("input_1.txt") == false) {
			return false;
		}
		rotatePiece(game.piece, game.piece_count);
	}

	bool run() {
		// TODO: implement this @thanhminhmr
	}
};

void Game::rotatePiece(PieceState* piece, size_t piece_count) {
	// TODO: implement this
}
#endif // !_GAME_H_
