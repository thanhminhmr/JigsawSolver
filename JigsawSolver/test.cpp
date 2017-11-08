#include "std.h"
#include <iostream>
int main(int argc, char** argv){
	InOutStream io;
  
	State state = io.readFile("../Doc/de_1_rand_reformat.txt");
  	//io.printFile(state, "output.txt");
  	
  	Piece* pieces = state.pieces;
  	for (int j = 0; j < state.piece_count; j ++) {
  		for (int i = 0; i < pieces[j].size; i ++) {
  			std::cout << pieces[j].angle[i].start.x << " " << pieces[j].angle[i].start.y << " ";
  		}
  		std::cout << endl;
	}
	return 0;
}

