#include "State.h"
#include <iostream>
using namespace std;

void State::push(Piece &piece)
{
	pieces.push_back(piece);
	pieces.back().id = pieces.size() - 1;
}

State::State(int N)
{
	pieces = vector<Piece>(N);
}

void push_vpair(vector<vPair>& res, Vertex *a, Vertex *b, int child_1, int child_2)
{
	vPair tmp(a, b, child_1, child_2);
	if (tmp.compatibility > 0) res.push_back(tmp);
	if ((a->angle + b->angle) != 2 * PI)
	{
		tmp = vPair(b, a, child_2, child_1);
		if (tmp.compatibility > 0) res.push_back(tmp);
	}
}

void State::get_vPairs(vector<vPair>& res)
{
	res.clear();
	for (int i = 0; i < pieces.size(); i++)
	{
		if (!pieces[i].exist) continue;
		for (int j = i + 1; j < pieces.size(); j++)
		{
			if (!pieces[j].exist) continue;
			for (int m = 0; m < pieces[i].vertices.size(); m++)
				for (int n = 0; n < pieces[j].vertices.size(); n++)
				{
					push_vpair(res, &(pieces[i].vertices[m]), &(pieces[j].vertices[n]), i, j);

					if (!pieces[i].is_frame)
					{
						Piece flip = pieces[i].flip();
						push_vpair(res, &flip.vertices[flip.vertices.size() - 1 - m], &(pieces[j].vertices[n]), i, j);
					}
					else
					{
						Piece flip = pieces[j].flip();
						push_vpair(res, &(pieces[i].vertices[m]), &flip.vertices[flip.vertices.size() - 1 - n], i, j);
					}
				}
		}
	}
}
