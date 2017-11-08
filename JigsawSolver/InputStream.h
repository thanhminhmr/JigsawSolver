#ifndef _INPUTSTREAM_H_
#define _INPUTSTREAM_H_

#include <string>
#include "std.h"

class InputStream {
public: 
	InputStream(){}
	Piece * readFile(std::string filename);

	static int piece_count; 

};
#endif