#ifndef _GAME_H_
#define _GAME_H_

class Game {
protected:
	// Piece data ==========
	struct PieceState {
		size_t id;
		size_t state_count;
		Piece state[8];
	};
	struct PieceData {
		size_t piece_count;
		PieceState* piece;
	};
	PieceData game;

	// Board data ==========
	size_t board_id;
	Board board;
	
protected:
	// read Board and Piece(s) from file
	bool readFile(const char* filename) {
		Point points[MAX_POINT_COUNT];

		FILE *fin = fopen(filename, "r");
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
				int x, y;
				fscanf(fin, "%d%d", &x, &y);
				points[j] = Point(x, y);
			}
			game.piece[i].state[0] = Piece(points, point_count);
		}

		// read Board ==========
		size_t point_count;
		fscanf(fin, "%zu%zu", &board_id, &point_count);
		for (size_t j = 0; j < point_count; j += 1) {
			int x, y;
			fscanf(fin, "%d%d", &x, &y);
			points[j] = Point(x, y);
		}
		Piece piece(points, point_count, false);
		board = Board(&piece, 1);

		fclose(fin);
		return true;
	}

	bool writeFile(const char* filename) {
		FILE *fout = fopen(filename, "w");
		if (fout == NULL) {
			printf("Unable to open file.\n");
			return false;
		}

		// read Piece ==========
		fprintf(fout, "%zu\n", game.piece_count);
		for (size_t i = 0; i < game.piece_count; i += 1) {
			for (size_t k = 0; k < game.piece[i].state_count; k++) {
				fprintf(fout, "%zu %zu ", game.piece[i].id, game.piece[i].state[k].size);
				for (size_t j = 0; j < game.piece[i].state[k].size; j += 1) {
					fprintf(fout, "%d %d ", game.piece[i].state[k].points[j].x, game.piece[i].state[k].points[j].y);
				}
				fprintf(fout, "\n");
			}
			fprintf(fout, "\n");
		}
		fprintf(fout, "\n");

		// read Board ==========
		fprintf(fout, "%zu %zu ", board_id, board.pieces[0].size);
		for (size_t j = 0; j < board.pieces[0].size; j += 1) {
			fprintf(fout, "%d %d ", board.pieces[0].points[j].x, board.pieces[0].points[j].y);
		}

		fclose(fout);
		return true;
	}


private:
	// generate all states of all pieces
	static inline bool isStateExist(const Piece* state, size_t state_count, const Piece& piece) {
		for (size_t i = 0; i < state_count; i++) {
			if (piece == state[i]) {
				return true;
			}
		}
		return false;
	}

protected:
	// generate all states of all pieces
	static void generatePieceState(PieceState& piece_state) {
		// generate rotation of initPiece
		Piece piece_tmp = piece_state.state[0];
		for (size_t i = 1; i < 4; i++) {
			piece_tmp = piece_tmp.rotate();
			if (isStateExist(piece_state.state, piece_state.state_count, piece_tmp)) {
				break;
			} else {
				piece_state.state[piece_state.state_count] = piece_tmp;
				piece_state.state_count++;
			}
		}
		// generate rotation of flipped piece
		piece_tmp = piece_tmp.flip();
		for (size_t i = 0; i < 4; i++) {
			piece_tmp = piece_tmp.rotate();
			if (isStateExist(piece_state.state, piece_state.state_count, piece_tmp)) {
				break;
			} else {
				piece_state.state[piece_state.state_count] = piece_tmp;
				piece_state.state_count++;
			}
		}
	}

public:
	Game() {}
	~Game() {}

	// wake up and do things
	bool startup() {
		if (readFile("input_1.txt")) {
			for (size_t piece_index = 0; piece_index < game.piece_count; piece_index++) {
				generatePieceState(game.piece[piece_index]);
			}
			return true;
		}
		return false;
	}

	void run() {
		// TODO: implement this @thanhminhmr
	}
};

#endif // !_GAME_H_
