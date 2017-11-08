#include "std.h"
using namespace std;
/**
* InOutStream.h
* Read and print State from file
*/
class InOutStream {
public: 
	InOutStream(){}
	inline State readFile(const char* filename);
	inline void printFile(State state, const char* filename);
	inline void print(State state);
};

inline State InOutStream::readFile(const char* filename) {
  State state;
  Piece *pieces;
  Point *points;
  int id_tmp, point_count;
  int x_tmp, y_tmp;

  FILE *in;
  in = fopen(filename, "r");
  if (in != NULL) { 
    fscanf (in, "%d\n", &state.piece_count); 
    pieces = new Piece[state.piece_count];  
    for (int i = 0; i < state.piece_count; i++) {
      fscanf(in, "%d%d", &id_tmp, &point_count);
      points = new Point[point_count];
      for (int j = 0; j < point_count; j++) { 
        fscanf(in, "%d%d", &x_tmp, &y_tmp);
        Point point_tmp((int8_t) x_tmp, (int8_t) y_tmp);
        points[j] = point_tmp;
      }
      Piece piece_tmp(points, point_count);
      pieces[i] = piece_tmp;
    }
    fclose(in);
    state.pieces = pieces;
    return state;
  }
  else printf("%s\n", "Unable to open file");
}

inline void InOutStream::print(State state)  {
  Piece* pieces = state.pieces;
  printf("%d\n", state.piece_count);
  for (int i = 0; i < state.piece_count; i++) {
    printf("%d %d ", i + 1, pieces[i].size);
    for (int j = 0; j < pieces[i].size; j++) {
      printf("%d %d ", (int16_t) pieces[i].point[j].x, (int16_t) pieces[i].point[j].y);
    }
    printf("\n");
  }
}

 inline void InOutStream::printFile(State state, const char* filename) {
 	FILE* out;
 	out = fopen(filename, "w");
 	
 	Piece* pieces = state.pieces;
  	fprintf(out, "%d\n", state.piece_count);
  	for (int i = 0; i < state.piece_count; i++) {
    	fprintf(out, "%d %d ", i + 1, pieces[i].size);
    	for (int j = 0; j < pieces[i].size; j++) {
      	fprintf(out, "%d %d ", (int16_t) pieces[i].point[j].x, (int16_t) pieces[i].point[j].y);
    }
    fprintf(out, "\n");
  	}
 	fclose(out);
 }

