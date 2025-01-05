#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>

using namespace std;
/*
	Given array L of N numbers, each Li is the index of array L itself.
	From Li we can to to L[Li].
	Choose any start, on the path each element can only be accessed once.
	2 <= N <= 5e5
	1 <= Li <= N
	Li != i
*/

// dfs
bool dfs(int u, vector<int>& L, vector<bool>& visited, vector<int>& s, vector<int>& max_vertex_from) {
	visited[u] = 1;
	s.push_back(u);
	int v = L[u];
	if (!visited[v]) {
		dfs(v, L, visited, s, max_vertex_from);
		// say that this vertex is not part of a cycle
		// bc vertex in a cycle will be handle when cycle detected
		if (max_vertex_from[u] == -1) {
			max_vertex_from[u] = max_vertex_from[v] + 1;
		}
	}
	else {
		// find v in stack
		int pos = -1;
		for (int i = 0; i < s.size(); ++i) {
			if (s[i] == v) {
				pos = i;
				break;
			} 
		}
		// cycle exist
		if (pos != -1) {
			int total_vertex = s.size() - pos - 1;
			for (int i = pos; i < s.size(); ++i) {
				max_vertex_from[s[i]] = total_vertex;
			}
		} else {
			max_vertex_from[u] = max_vertex_from[v] + 1;
		}
		
	}
	// release vertex u
	s.pop_back();
	return true;
}

int getMaxVisibleWebpages(int N, vector<int> L) {
	vector<bool> visited(N, 0);
	vector<int> s;
	vector<int> max_vertex_from(N, -1);
	int result = 1;

	// substract 1 for simplicity in indexing
	for (int i = 0; i < N; ++i) {
		L[i]--;
	}

	for (int i = 0; i < N; ++i) {
		if (!visited[i]) {
			dfs(i, L, visited, s, max_vertex_from);
		}
		result = max(result, max_vertex_from[i] + 1);
	}
	for (int i = 0; i < N; ++i) {
		cout << max_vertex_from[i] << ' ';
	}
	cout << endl;
	cout << result << endl;
	return result;
}

bool test1() {
	int N = 4;
	vector<int> L{4, 1, 2, 1};
	// assume index start at 1
	//  L[3] = 2 => L[2] = 1 => L[1] = 4 => L[4] = 1
	int expected = 4;
	int actual = getMaxVisibleWebpages(N, L);
	return expected == actual;
}

bool test2() {
	int N = 5;
	vector<int> L{4, 3, 5, 1, 2};
	// 
	int expected = 3;
	int actual = getMaxVisibleWebpages(N, L);
	return expected == actual;
}

bool test3() {
	int N = 5;
	vector<int> L{2, 4, 2, 2, 3};
	int expected = 4;
	int actual = getMaxVisibleWebpages(N, L);
	return expected == actual;
}

int main() {
	cout << test1() << endl;
	cout << test2() << endl;
	cout << test3() << endl;
	return 0;
}