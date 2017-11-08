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

int main(int argc, char** argv){
	InOutStream is;
	State state = is.readFile("../Doc/de_1_rand_reformat.txt");
  cout << state;
	return 0;
}

