#include "Piece.h"

Piece::Piece()
{
	this->exist = true;
	this->is_frame = false;
	child_1 = child_2 = -1;
}

Piece::Piece(const Piece & other)
{
	*this = other;
}

void Piece::push(int x, int y)
{
	vertices.push_back(Vertex(geometric::Point(x, y), this, (int)vertices.size()));
}

void Piece::push(geometric::Point p)
{
	push(p.x, p.y);
}

void Piece::compute_angles()
{
	for (int i = 0; i < vertices.size(); i++)
	{
		int before = int((i - 1 + vertices.size()) % vertices.size());
		int after = int((i + 1) % vertices.size());
		vertices[i].compute_angle(vertices[before], vertices[after]);
	}
}

void Piece::move(geometric::Point v)
{
	for (int i = 0; i < vertices.size(); i++)
	{
		vertices[i].move(v);
	}
}

bool Piece::rotate(double angle, geometric::Point center)
{
	Piece tmp = *this;
	for (int i = 0; i < vertices.size(); i++)
	{
		if (!tmp.vertices[i].rotate(angle, center))
			return false;
	}
	*this = tmp;
	return true;
}

void Piece::print() const
{
	for each (Vertex vertex in vertices)
	{
		vertex.print();
		cout << endl;
	}
}

void Piece::operator=(const Piece& other)
{
	this->vertices = other.vertices;
	this->child_1 = other.child_1;
	this->child_2 = other.child_2;
	this->exist = other.exist;
	this->is_frame = other.is_frame;
	for (int i = 0; i < vertices.size(); i++)
	{
		vertices[i].parent = this;
	}
}

Piece Piece::flip()
{
	Piece res;
	for (int i = vertices.size() - 1; i >= 0; i--)
	{
		res.push(-vertices[i].point.x, vertices[i].point.y);
	}
	res.compute_angles();
	return res;
}