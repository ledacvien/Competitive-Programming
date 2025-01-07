#include <bits/stdc++.h>

using namespace std;

/*
	The lock is a round circle with N integers 3 <= N <= 5e7
	code is an array with M integers
	return minimum time to open the lock
*/


long long calcDistance(int a, int b, int N) {
	// 1 a2 3 b4 5 6 7 8 9 {10
	// make sure b always greater
	if (a > b) {
		int temp = a;
		a = b;
		b = temp;
	}
	return 1LL * min(b-a, a + N - b);
}

long long getMinCodeEntryTime(int N, int M, vector<int> C) {
	long long result = 0;

	result += calcDistance(1, C[0], N);
	for (int i = 1; i < M; ++i)
	{
		result += calcDistance(C[i], C[i-1], N);
	}
	return result;
}

bool test1() {
	int N = 3, M = 3;
	vector<int> C{1, 2, 3};
	int expected = 2;
	int actual = getMinCodeEntryTime(N, M, C);
	cout << actual << endl;
	return actual == expected;
}

bool test2() {
	int N = 10, M = 4;
	vector<int> C{9, 4, 4, 8};
	// 1 + 6 + 0 + 4 = 11
	int expected = 11;
	int actual = getMinCodeEntryTime(N, M, C);
	cout << actual << endl;
	return actual == expected;
}

int main() {
	cout << test1() << endl;
	cout << test2() << endl;
	return 0;
}