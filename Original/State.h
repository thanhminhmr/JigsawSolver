#pragma once
#include "vPair.h"
#include <vector>
using namespace std;

class State
{
public:
	vector<Piece> pieces;
	void push(Piece &piece);
	State(int N);
	void get_vPairs(vector<vPair>& vpairs);
};