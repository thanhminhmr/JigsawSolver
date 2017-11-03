#pragma once
#include <string>
#include <queue>
#include <fstream>
#include "State.h"
using namespace std;

class InputReader
{
public:
	static queue<int> input;
	static void getInputString(string str);
	static int read();
	static int N;
};

State readInput(char* fileName);