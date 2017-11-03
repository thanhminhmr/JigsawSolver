#pragma once
#include <vector>
#include "Vertex.h"
using namespace std;

class Piece
{
public:
	vector<Vertex> vertices;
	bool exist;
	bool is_frame;
	int child_1, child_2;
	int id;

	Piece();
	Piece(const Piece& other);
	void operator=(const Piece& other);
	void push(int x, int y);
	void push(geometric::Point p);
	void compute_angles();
	void move(geometric::Point v);
	bool rotate(double angle, geometric::Point center);
	void print() const;
	Piece flip();
};
