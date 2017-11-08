#include "std.h"

#include <stdio.h>
#include <stdlib.h>
using namespace std;

State InOutStream::readFile(string filename) {
  State state;
  ifstream in(filename);
  if (in.is_open()){ 
    in >> state;
    return state;
  }
  else cout << "Unable to open file"; 
}

void InOutStream::printFile(State state, string filename)  {
  ofstream out(filename);
  out << state;
}

int main(int argc, char** argv){
	InOutStream io;
	State state = io.readFile("../Doc/de_1_rand_reformat.txt");
  io.printFile(state, "output.txt");
  cout << state;
	return 0;
}

