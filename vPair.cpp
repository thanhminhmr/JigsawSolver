#include "vPair.h"
#include <algorithm>

vPair::vPair(Vertex * a, Vertex * b, int child_1, int child_2)
{
	this->a = a;
	this->b = b;
	this->result.child_1 = child_1;
	this->result.child_2 = child_2;
	this->result.is_frame = a->parent->is_frame || b->parent->is_frame;
	get_compatibility();
}

int try_get_cmp(Vertex& a, Vertex& b, Vertex& _b, Vertex& a_, Piece& result)
{
	geometric::Point
		A = a.point,
		_B = _b.point,
		A_ = a_.point;

	if (!b.parent->rotate(geometric::compute_angle(A_, A, _B), A))
		if (!a.parent->rotate(geometric::compute_angle(_B, A, A_), A))
			return -1;

	if (geometric::check_polygon_intersect(*a.parent, *b.parent))
		return -1;

	int cmp = 0;
	int count = 0;
	Vertex *pa = &a, *pb = &b,
		*first_a, *first_b, *last_a, *last_b;
	first_a = pa->next();
	first_b = pb->prev();
	bool possible_duplicate = false;
	if (pa->next()->point == pb->prev()->point)
	{
		pa = pa->next();
		first_a = first_a->next();
		pb = pb->prev();
		if ((pa->angle + pb->angle) == 2 * PI)
		{
			possible_duplicate = true;
			first_b = first_b->prev();
		}
		if ((pa->angle + pb->angle) == PI)
			first_b = first_b->prev();
	}
	last_a = pa;
	last_b = pb;
	for (int i = 0; i < min(a.parent->vertices.size(), b.parent->vertices.size()); i++)
	{
		if (pa->point == pb->point)
		{
			count++;
			if ((pa->angle == PI / 2) || (pb->angle == PI / 2))
				cmp += 2;
			else
				if ((pa->angle + pb->angle) == 2 * PI)
					cmp += 5;
				else
					cmp += 1;
			last_a = pa;
			last_b = pb;
			pa = pa->prev();
			pb = pb->next();
		}
		else
			break;
	}
	if (possible_duplicate)
	{
		if (a.parent->vertices.size() != b.parent->vertices.size()) return -1;
		if (count != a.parent->vertices.size()) return -1;
	}
	bool
		a_perfect = last_a == first_a,
		b_perfect = last_b == first_b;

	if (((last_a->angle + last_b->angle) == PI) || ((last_a->angle + last_b->angle) == 2 * PI))
		last_b = last_b->next();
	else b_perfect = false;

	last_a = last_a->prev();

	if (!a_perfect)
	{
		while (first_a != last_a)
		{
			result.push(first_a->point);
			first_a = first_a->next();
		}
		result.push(last_a->point);
	}

	if (!b_perfect)
	{
		while (last_b != first_b)
		{
			result.push(last_b->point);
			last_b = last_b->next();
		}
		result.push(first_b->point);
	}
	result.compute_angles();
	return cmp;
}

void vPair::get_compatibility()
{
	compatibility = 0;
	Piece
		tmp_piece_a = *this->a->parent,
		tmp_piece_b = *this->b->parent;

	Vertex *a = &tmp_piece_a.vertices[this->a->id];
	Vertex *b = &tmp_piece_b.vertices[this->b->id];

	tmp_piece_b.move(this->a->point - this->b->point);

	compatibility = try_get_cmp(*a, *b, *b->prev(), *a->next(), result);
}

bool compare_func(vPair i, vPair j)
{
	return i.compatibility > j.compatibility;
}
