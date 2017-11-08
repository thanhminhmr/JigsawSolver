#include "std.h"

int main(int argc, char** argv){
	InOutStream io;
  
	State state = io.readFile("../Doc/de_1_rand_reformat.txt");
  	io.printFile(state, "output.txt");
  
	return 0;
}

