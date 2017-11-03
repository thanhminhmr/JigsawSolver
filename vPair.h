#pragma once
#include "Piece.h"

class vPair
{
public:
	Vertex *a, *b;
	int compatibility;
	Piece result;

	vPair(Vertex *a, Vertex *b, int child_1, int child_2);
	void get_compatibility();
};

bool compare_func(vPair i, vPair j);