#include <vector>
#include <utility>
#include <map>
#include <queue>
#include <iostream>

using namespace std;

/*
	Find way out of matrix
	G = '.' cell empty
	G = 'S' starting position
	G = 'E' exit (at least one)
	G = '#' wall
	G = 'a' .. 'z' portal

	Algo: BFS
	1. map between portal
		map<pair<int, int>, vector<pair<int, int>>> portals;
	2. BFS 
*/

pair<int, int> find_start(int& R, int& C, vector<vector<char>> G) {
	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) 
			if (G[i][j] == 'S')
				return std::make_pair(i, j);
	}
	return std::make_pair(-1, -1);
}

int getSecondsRequired(int R, int C, vector<vector<char>> G) {
	// down: x+1, y 	up:	 x-1, y 	left: x, y-1 	right: x, y+1 
	const int dx[4] = {1, -1, 0, 0};
	const int dy[4] = {0, 0, -1, 1};
	// mark[i][j] = true -> possible
	vector<vector<bool>> mark(R, vector<bool>(C, true));
	pair<int, int> start;
	queue<pair<pair<int, int>, int>> Q;
	map<char, vector<pair<int, int>>> portals;
	int result = -1;

	// find start position
	start = find_start(R, C, G);
	// find and connect all portals
	// mark = false if cell is a wall '#'
	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) {
			char cell = G[i][j];
			if (cell >= 'a' && cell <= 'z') {
				portals[cell].push_back(std::make_pair(i, j));
			} else if (cell == '#') {
				mark[i][j] = false;
			}
		}
	}

	// for (auto& it : portals) {
	// 	cout << it.first << '\t';
	// 	for (auto& i : it.second) {
	// 		printf("(%d,%d) ", i.first, i.second);
	// 	}
	// 	cout << endl;
	// }

	// BFS
	Q.push({start, 0});
	mark[start.first][start.second] = false;
	while (Q.size()) 
	{
		pair<pair<int, int>, int> top = Q.front();
		pair<int, int> pos = top.first;
		int count = top.second;
		Q.pop();

		char cell = G[pos.first][pos.second];

		// printf("cell: %c - (%d, %d)\n", cell, pos.first, pos.second);

		if (cell == 'E') {
			result = count;
			break;
		}

		count++;
		// if cell is a portal then get all possible place it could teleport to
		if (cell >= 'a' && cell <= 'z') {
			for (pair<int, int>& p : portals[cell]) {
				if (mark[p.first][p.second]) {
					mark[p.first][p.second] = false;
					Q.push(std::make_pair(p, count));
				}
			}
		}
		// going to adjacent cells
		for (int i = 0; i < 4; ++i) {
			int ix = pos.first + dx[i];
			int jx = pos.second + dy[i];
			// empty pos
			if (ix >= 0 && ix < R && jx >= 0 && jx < C && mark[ix][jx]) {
				mark[ix][jx] = false;
				Q.push(std::make_pair(std::make_pair(ix, jx), count));
			}
		}
	}

	// cout << result << endl;
	return result;
}

bool test1() {
	int R = 3, C = 3;
	vector<vector<char>> G{
		{'.', 'E', '.'},
		{'.', '#', 'E'},
		{'.', 'S', '#'}
	};
	int expected = 4;
	int actual = getSecondsRequired(R, C, G);
	return expected == actual;
}

bool test2() {
	int R = 3, C = 4;
	vector<vector<char>> G{
		{'a', '.', 'S', 'a'},
		{'#', '#', '#', '#'},
		{'E', 'b', '.', 'b'}
	};
	int expected = -1;
	int actual = getSecondsRequired(R, C, G);
	return expected == actual;
}

bool test3() {
	int R = 3, C = 4;
	vector<vector<char>> G{
		{'a', 'S', '.', 'b'},
		{'#', '#', '#', '#'},
		{'E', 'b', '.', 'a'}
	};
	int expected = 4;
	int actual = getSecondsRequired(R, C, G);
	return expected == actual;
}

bool test4() {
	int R = 1, C = 9;
	vector<vector<char>> G{
		{'x', 'S', '.', '.', 'x', '.', '.', 'E', 'x'}
	};
	int expected = 3;
	int actual = getSecondsRequired(R, C, G);
	return expected == actual;
}

int main() {
	cout << test1() << endl;
	cout << test2() << endl;
	cout << test3() << endl;
	cout << test4() << endl;
	return 0;
}