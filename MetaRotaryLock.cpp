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

/*  Hard version
	Algo: At every point i, one of the lock must be i-1 and the other canbe
		at any position from C[0] -> C[i-2] or 1.
		We can define dp[i][j] as best solution at position i, where one lock is at i, and the other at j
		Then the next i+1 canbe caculated by:

		- Case 1: jumping from i
		dp[i+1][j] = min(dp[i+1][j], dp[i][j] + calcDistance(C[i+1], C[i], N))

		- Case 2: jumping from j
		dp[i][i+1] = min(dp[i][i+1], dp[i][j] + calcDistance(C[i+1], C[j], N))
		 Since the order doens't matter:
		dp[i+1][i] = min(dp[i+1][i], dp[i][j] + calcDistance(C[i+1], C[j], N))

		Note: I don't fking know why dp[i+1][i] can be calculated from dp[i][j]
			I also don't fking know why that indicates jumping from j
			It make no fking sense. And I achieved that by accident
			My best asumption is at this point, dp[i][j] is not indicating what it supposed to be.
			But rather representing i - the current step, j - the latest position that either locks jumped to.
				And by calling the calcDistance, we are trying to utilize the other lock.
			It works like magic
*/
long long getMinCodeEntryTimeHard2(int N, int M, vector<int> C) {
	long long result = 1e18;

	C.insert(C.begin(), 1);

	vector<vector<long long>> dp(M+1, vector<long long>(M+1, 1e18));
	dp[0][0] = 0;

	// base case if one lock is used
	for (int i = 1; i <= M; ++i) {
		long long dist = calcDistance(C[i], C[i-1], N);
		dp[0][i] = dp[0][i-1] + dist;
		dp[i][0] = dp[i-1][0] + dist;
	}

	for (int i = 0; i < M; ++i) {
		cout << "begin: " << i << endl;
		// dp[i+1][i] = dp[i][0] + calcDistance(C[0], C[i+1], N);
		for (int j = 0; j < i; ++j) {
			// cout << "inside j\n";
			printf("dp[%d][%d] = %lld\n", i, j, dp[i][j]);
			dp[i+1][j] = min(dp[i+1][j], dp[i][j] + calcDistance(C[i+1], C[i], N));
			dp[i+1][i] = min(dp[i+1][i], dp[i][j] + calcDistance(C[i+1], C[j], N));
			printf("dp[%d][%d] = %lld\n", i+1, j, dp[i+1][j]);
			printf("dp[%d][%d] = %lld\n", i+1, i, dp[i+1][i]);
		}
	}

	for (int i = 0; i <= M; ++i) {
		for (int j = 0; j <= M; ++j) {
			cout << dp[i][j] << ' ';
		}
		cout << endl;
	}

	for (int j = 0; j <= M; ++j) {
		result = min(result, dp[M][j]);
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

bool test1H() {
	int N = 3, M = 3;
	vector<int> C{1, 2, 3};
	int expected = 2;
	int actual = getMinCodeEntryTimeHard2(N, M, C);
	cout << actual << endl;
	return actual == expected;
}

bool test2H() {
	int N = 10, M = 4;
	vector<int> C{9, 4, 4, 8};
	int expected = 6;
	int actual = getMinCodeEntryTimeHard2(N, M, C);
	cout << actual << endl;
	return actual == expected;
}

bool test3H() {
	int N = 5, M = 3;
	vector<int> C{2, 4, 1};
	int expected = 3;
	int actual = getMinCodeEntryTimeHard2(N, M, C);
	cout << actual << endl;
	return actual == expected;
}

int main() {
	// cout << test1() << endl;
	// cout << test2() << endl;
	cout << test1H() << endl << endl;
	cout << test2H() << endl << endl;
	cout << test3H() << endl << endl;
	return 0;
}