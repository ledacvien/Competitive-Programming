#include <bits/stdc++.h>

using namespace std;

/* A photo consists of N cells in a row, numbered from 1 to N in order, and can be represented by a 
	string C of length N. Each cell i-th is one of the following types:
		Ci = 'P' it is allowed to contain a photographer
		Ci = 'A' ------------------------ an actor
		Ci = 'B' ------------------------ a backdrop
		Ci = '.' must be left empty
	A photo consist of a photographer, an actor, and a backdrop, such that each of them is placed in
	a valid cell, and such that the actor is between the photographer and the backdrop.
	Such photo is considered artistic if the distance between the photographer and the actor is 
	between X and Y cells (inclusive), and so does the distance between the actor and backdrop. 
	The distance between cells i and j is |i-j|
	X <= d(P, A), d(A, B) <= Y

	Determine number of differenct artistic photos which could potentially be taken at the set.
	Two photos are considered different if they have diff photographer cell, actor, backdrop
*/

int getArtisticPhotographCount(int N, string C, int X, int Y) {
	int result = 0;
	for (int i = 0; i < N; ++i)
	{
		// X <= j-i <= Y
		for (int j = i + X; j < N && j <= i + Y; ++j)
		{
			// i < j < k <= j+Y
			for (int k = j + X; k < N && k <= j + Y; ++k)
			{
				// P A B
				if (C[i] == 'P' && C[j] == 'A' && C[k] == 'B') {
					result++;
				}
				// B A P
				if (C[i] == 'B' && C[j] == 'A' && C[k] == 'P') {
					result++;
				}
			}
		}
	}

	return result;
}

int test1() {
	int N = 5, X = 1, Y = 2;
	string C = "APABA";
	return getArtisticPhotographCount(N, C, X, Y);
}

int test2() {
	int N = 5, X = 2, Y = 3;
	string C = "APABA";
	return getArtisticPhotographCount(N, C, X, Y);
}

int test3() {
	int N = 8, X = 1, Y = 3;
	string C = ".PBAAP.B";
	return getArtisticPhotographCount(N, C, X, Y);
}

int main() {

	cout << test1() << endl;
	cout << test2() << endl;
	cout << test3() << endl;
	return 0;
}