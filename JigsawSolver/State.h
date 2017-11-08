#ifndef _STATE_H_
#define _STATE_H_
#include "std.h"
using namespace std;

class State {
public:
	int piece_count;
	Piece* pieces;
	//Board board;
	inline ~State() {}
	inline State() : piece_count(0), pieces(NULL) {} 
	//Board khong co Board(NULL)
	friend istream& operator>> (istream& is, State& state);
	friend ostream& operator<< (ostream& os, const State& state);              
};

istream& operator>>(istream& is, State &state) {
  Piece *pieces;
  Point *points;
  int id_tmp, point_count;
  int x_tmp, y_tmp;

  is >> state.piece_count;
  pieces = new Piece[state.piece_count];  
   for (int i = 0; i < state.piece_count; i++) {
   		is >> id_tmp >> point_count;
   		points = new Point[point_count];
   		for (int j = 0; j < point_count; j++) { 
   			is >> x_tmp >> y_tmp;
        	Point point_tmp((int8_t) x_tmp, (int8_t) y_tmp);
   			points[j] = point_tmp;
   		}
      Piece piece_tmp(points, point_count);
      pieces[i] = piece_tmp;
   	}
    state.pieces = pieces;
  }

ostream& operator<< (ostream& os, const State& state) {
	Piece* pieces = state.pieces;
	os << state.piece_count << endl;
	for (int i = 0; i < state.piece_count; i++) {
		os << i + 1 << " " << pieces[i].size << " ";
    for (int j = 0; j < pieces[i].size; j++) {
    	os << (int16_t) pieces[i].getPoints()[j].x << " " << (int16_t) pieces[i].getPoints()[j].y << " "; 
    }
   	os << endl;
  }
}

#endif
