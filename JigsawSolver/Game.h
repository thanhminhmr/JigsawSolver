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
	
	// Progress data =======
	struct PiecePlace {
		size_t id;
		Piece piece;
	};
	struct PieceProgress {
		size_t step;
		size_t count;
		PiecePlace* place;
		bool* mask;

		size_t board_id;
		const Board* board;
	};
	PieceProgress progress;
	
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
			progress.step = 0;
			progress.count = 0;
			progress.place = memalloc<PiecePlace>(game.piece_count);
			progress.mask = memalloc<bool>(game.piece_count);
			progress.board_id = board_id;
			progress.board = &board;
			return true;
		}
		return false;
	}

	void run() {
		// TODO: implement this @thanhminhmr
		for (size_t i = 0; i < game.piece_count; i++) {
			progress.mask[i] = false;
		}
		if (loop(game, progress, board)) {
			writeProgress("output.txt", progress);
		}
	}


	static bool writeProgress(const char* filename, const PieceProgress& progress) {
		FILE *fout = fopen(filename, "w");
		if (fout == NULL) {
			printf("Unable to open file.\n");
			return false;
		}

		// write Piece ==========
		fprintf(fout, "%zu\n", progress.count);
		for (size_t i = 0; i < progress.count; i += 1) {
			fprintf(fout, "%zu %zu ", progress.place[i].id, progress.place[i].piece.size);
			for (size_t j = 0; j < progress.place[i].piece.size; j += 1) {
				fprintf(fout, "%d %d ", progress.place[i].piece.points[j].x, progress.place[i].piece.points[j].y);
			}
			fprintf(fout, "\n");
		}
		fprintf(fout, "\n");

		// write Board ==========
		fprintf(fout, "%zu %zu ", progress.board_id, progress.board->pieces[0].size);
		for (size_t j = 0; j < progress.board->pieces[0].size; j += 1) {
			fprintf(fout, "%d %d ", progress.board->pieces[0].points[j].x, progress.board->pieces[0].points[j].y);
		}

		fclose(fout);
		return true;
	}

	static bool writeProgress(size_t count, const PieceProgress& progress) {
		char filename[32];
		snprintf(filename, 31, "output_%zu.txt", count);
		FILE *fout = fopen(filename, "w");
		if (fout == NULL) {
			printf("Unable to open file.\n");
			return false;
		}

		// write Piece ==========
		fprintf(fout, "%zu\n", progress.count);
		for (size_t i = 0; i < progress.count; i += 1) {
			fprintf(fout, "%zu %zu ", progress.place[i].id, progress.place[i].piece.size);
			for (size_t j = 0; j < progress.place[i].piece.size; j += 1) {
				fprintf(fout, "%d %d ", progress.place[i].piece.points[j].x, progress.place[i].piece.points[j].y);
			}
			fprintf(fout, "\n");
		}
		fprintf(fout, "\n");

		// write Board ==========
		fprintf(fout, "%zu %zu ", progress.board_id, progress.board->pieces[0].size);
		for (size_t j = 0; j < progress.board->pieces[0].size; j += 1) {
			fprintf(fout, "%d %d ", progress.board->pieces[0].points[j].x, progress.board->pieces[0].points[j].y);
		}

		fclose(fout);
		return true;
	}

	static bool Game::loop(const PieceData& game, PieceProgress& progress, const Board& board);
};
//*
bool Game::loop(const PieceData& game, PieceProgress& progress, const Board& board) {
	// take the first Angle of Board
	// TODO: take the smallest Angle of Board, if needed. @thanhminhmr
	bool piece_from_ref = (board.size == 0);
	const Piece& board_piece = piece_from_ref ? *board.piecerefs[0] : board.pieces[0];
	const Point& board_point = board_piece.points[0];
	const Angle& board_angle = board_piece.angles[0];

	// find the suitable Piece
	for (size_t piece_index = 0; piece_index < game.piece_count; piece_index++) {
		if (progress.mask[piece_index] == false) {
			progress.mask[piece_index] = true;

			const PieceState& piece_state = game.piece[piece_index];

			// find the suitable PieceState
			for (size_t state_index = 0; state_index < piece_state.state_count; state_index++) {
				const Piece& piece = piece_state.state[state_index];

				// find the suitable Angle
				for (size_t angle_index = 0; angle_index < piece.size; angle_index++) {
					const Point &piece_point = piece.points[angle_index];
					const Angle &piece_angle = piece.angles[angle_index];
					if (board_angle.start == piece_angle.start) {
						// check if Board is subtractable
						Vector position(piece_point, board_point);
						if (board_piece.isContainable(piece, position)) {
							progress.place[progress.count].id = piece_state.id;
							progress.place[progress.count].piece = piece.move(position);
							progress.count += 1;
							progress.step += 1;
							if (progress.step & 255 == 0) {
								printf("%zu %zu\n", progress.step, progress.count);
								writeProgress(progress.step, progress);
							}
							if (progress.count == game.piece_count) {
								// done
								return true;
							} else {
								Board new_board = board.subtract(false, 0, 0, piece, angle_index, position);
								if (loop(game, progress, new_board)) {
									return true;
								}
							}
							progress.count -= 1;
						}
					}
				}
			}

			progress.mask[piece_index] = false;
		}
	}
	return false;
}
//*/
#endif // !_GAME_H_
