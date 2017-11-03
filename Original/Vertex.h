#pragma once
#include "Geometric.h"

class Piece;
class Vertex
{
public:
	geometric::Point point;
	Piece *parent;
	int id;
	double angle;

	Vertex(const geometric::Point& point, Piece *parent, int id);
	void compute_angle(const Vertex &before, const Vertex &after);
	Vertex* next() const;
	Vertex* prev() const;
	void move(geometric::Point v);
	bool rotate(double angle, geometric::Point center);
	void print();
};
