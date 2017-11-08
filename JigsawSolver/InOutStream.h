#include "std.h"
#ifndef _INPUTSTREAM_H_
#define _INPUTSTREAM_H_


class InOutStream {

public: 
	InOutStream(){}
	State readFile(std::string filename);
	void printFile(std::string filename);
};
#endif