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

// Hard version
// 1 <= N <= 300,000
// 1 <= X <= Y <= N
// Algo: precount the B, and P
//  artistic photo always in format PAB or BAP
//		0 1 2 3 4
//		A P A B A
//pB 	0 0 0 0 1 0
//pP 	0 0 1 1 1 1
long long getArtisticPhotographCountH(int N, string C, int X, int Y) {
	vector<int> prefixB(N+1, 0);
	vector<int> prefixP(N+1, 0);
	vector<int> posA;
	long long result = 0;

	for (int i = 0; i < N; ++i)
	{
		prefixB[i+1] = prefixB[i] + (C[i] == 'B' ? 1 : 0);
		prefixP[i+1] = prefixP[i] + (C[i] == 'P' ? 1 : 0);
		if (C[i] == 'A')
			posA.push_back(i);
	}

	for (int i : posA)
	{
		int leftX = max(0, i-X+1);
		int leftY = max(0, i-Y);
		int rightX = min(N, i+X);
		int rightY = min(N, i+Y+1);
		// calculate number of BAP
		result += 1LL * (prefixB[leftX] - prefixB[leftY]) * (prefixP[rightY] - prefixP[rightX]);

		// calculate number of PAB
		result += 1LL * (prefixP[leftX] - prefixP[leftY]) * (prefixB[rightY] - prefixB[rightX]);
	}

	return result;
}

void stresstest() {
	int correct = 0;
	for (int t = 0; t < 10000; ++t)
	{
		string s = "";
		int c;
		int N = rand() % 1000 + 1;
		for (int i = 0; i < N; ++i)
		{
			// random 0, 1, 2, 3
			c = rand() % 6;
			switch (c){
			case 0: 
				s += 'P';
				break;
			case 1: 
				s += 'A';
				break;
			case 2:
				s += 'B';
				break;
			case 3:
				s += '.';
				break;
			// over sampling B, P
			case 4:
				s += 'P';
				break;
			case 5:
				s += 'B';
				break;
			}
		}
		int X = rand() % 10 + 1;
		int Y = rand() % 100 + 1;
		int expected, actual;
		if (X <= Y) {
			expected = getArtisticPhotographCount(N, s, X, Y);
			actual = getArtisticPhotographCountH(N, s, X, Y);
		} else {
			expected = getArtisticPhotographCount(N, s, Y, X);
			actual = getArtisticPhotographCountH(N, s, Y, X);
		}

		if (expected != actual) {
			cout << s << '\n' << N << ' ' << X << ' ' << Y << endl;
			printf("expected: %d \nactual: %d\n", expected, actual);
		} else {
			correct++;
		}
	}

	cout << correct << endl;
	
}

int test1() {
	int N = 5, X = 1, Y = 2;
	string C = "APABA";
	return getArtisticPhotographCountH(N, C, X, Y);
}

int test2() {
	int N = 5, X = 2, Y = 3;
	string C = "APABA";
	return getArtisticPhotographCountH(N, C, X, Y);
}

int test3() {
	int N = 8, X = 1, Y = 3;
	string C = ".PBAAP.B";
	return getArtisticPhotographCountH(N, C, X, Y);
}

int test4() {
	int N = 20, X = 6, Y = 9;
	string C = "BPAPBABAPBBAAPPB";
	return getArtisticPhotographCount(N, C, X, Y);
}

int main() {

	// cout << test1() << endl;
	// cout << test2() << endl;
	// cout << test3() << endl;
	//cout << test4() << endl;
	stresstest();
	return 0;
}