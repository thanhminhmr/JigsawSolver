#ifndef _GAME_H_
#define _GAME_H_

class Game {
protected:
	struct PieceData {
		static const size_t MAX_COUNT = 16;
		size_t piece_id;
		size_t piece_count;
		Piece piece[MAX_COUNT];
	};
	size_t input_count;
	PieceData* input_piece;

protected:
	bool readFile(const char* filename) {
		static const size_t MAX_COUNT = 32;
		Point point[MAX_COUNT];

		FILE *fin = fopen(filename, "rb");
		if (fin == NULL) {
			printf("Unable to open file.\n");
			return false;
		}

		fscanf(fin, "%u", &input_count);
		input_piece = memalloc<PieceData>(input_count);

		for (size_t i = 0; i < input_count; i += 1) {
			size_t piece_id, point_count;

			fscanf(fin, "%u%u", &piece_id, &point_count);
			input_piece[i].piece_id = piece_id;
			input_piece[i].piece_count = 1;

			for (size_t j = 0; j < point_count; j += 1) {
				size_t x, y;
				fscanf(fin, "%u%u", &x, &y);
				point[j] = Point(x, y);
			}
			
			input_piece[i].piece[0] = Piece(point, point_count);
		}
		fclose(fin);
		return true;
	}

public:
	Game();
	~Game();
};

Game::Game() {}

Game::~Game() {}

#endif // !_GAME_H_
