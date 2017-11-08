#include "std.h"

class InOutStream {
public: 
	InOutStream(){}
	State readFile(std::string filename);
	void printFile(State state, std::string filename);
};
