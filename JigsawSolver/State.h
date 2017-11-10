#ifndef _STATE_H_
#define _STATE_H_
#include "std.h"
using namespace std;
/**
* State.h
* Save the state of everything after each step
*/
class State {
public:
	int piece_count; //number of pieces
	Piece* pieces;   //array of pieces
	//Board board;   //board
	inline ~State() {}
	inline State() : piece_count(0), pieces(NULL) {} 
	//Board khong co Board(NULL)        
};

#endif
