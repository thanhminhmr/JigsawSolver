#include "Vertex.h"
#include "Piece.h"

Vertex::Vertex(const geometric::Point& point, Piece *parent, int id)
{
	this->point = point;
	this->parent = parent;
	this->id = id;
}

void Vertex::compute_angle(const Vertex &before, const Vertex &after)
{
	angle = geometric::compute_angle(before.point, this->point, after.point);
}

Vertex* Vertex::next() const
{
	return &(parent->vertices[(id + 1) % parent->vertices.size()]);
}

Vertex* Vertex::prev() const
{
	return &(parent->vertices[(id - 1 + parent->vertices.size()) % parent->vertices.size()]);
}

void Vertex::move(geometric::Point v)
{
	point = point + v;
}

bool Vertex::rotate(double angle, geometric::Point center)
{
	return point.rotate(angle, center);
}

void Vertex::print()
{
	point.print();
}
