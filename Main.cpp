#include <iostream>
#include "State.h"
#include "InputReader.h"
using namespace std;

State state = readInput("input.txt");

void show_me(int root)
{
	cout << root << endl;
	int child_1 = state.pieces[root].child_1;
	int child_2 = state.pieces[root].child_2;
	cout << child_1 << " " << child_2 << endl;
	if (child_1 != -1)
	{
		show_me(child_1);
		show_me(child_2);
		imshow("child 1", geometric::drawPiece(state.pieces[child_1], 30));
		imshow("child 2", geometric::drawPiece(state.pieces[child_2], 30));
		imshow("result", geometric::drawPiece(state.pieces[root], 30));
		waitKey();
	}
}

void trace_result()
{
	int root;
	for (int i = 0; i < state.pieces.size(); i++)
		if (state.pieces[i].exist)
		{
			root = i;
			break;
		}
	show_me(root);
}

void backtrack(int depth)
{
	if (depth == InputReader::N)
		trace_result();
	vector<vPair> vpairs;
	state.get_vPairs(vpairs);
	if (vpairs.empty()) return;
	std::sort(vpairs.begin(), vpairs.end(), compare_func);
	for (int i = 0; i < vpairs.size(); i++)
	{
		state.push(vpairs[i].result);
		state.pieces.back().exist = true;
		state.pieces[vpairs[i].result.child_1].exist = false;
		state.pieces[vpairs[i].result.child_2].exist = false;
		backtrack(depth + 1);
		state.pieces.back().exist = false;
		state.pieces[state.pieces.back().child_1].exist = true;
		state.pieces[state.pieces.back().child_2].exist = true;
		state.pieces.pop_back();
	}
}

int main(void) {
	backtrack(0);
	getchar();
}