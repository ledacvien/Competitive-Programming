#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const double epsilon = 1e-6;

/*
	You are the manager of a mail room which is ferquently subject to theft. A period of N days is about to 
	occur, such that on ith day, the following sequence of events will occur in order:
	1. A package with value Vi $ will deliveried to mail room (Vi could be 0)
	2. You can choose to pay $C to enter mail room and collect all packages there
	3. With probability S, all packages currently in the mail room will get stolen

	Algo:
	dp[j][i] = maximum value when pick up at j then at i (j->i)
	dp[j][i] = max(dp[*][j]) + (Vi - C) + leftover[j][i]
	Vi - C: value when pickup today after subtract by cost
	leftover[j][i]: total value when not picked up from [j, i)
*/

double getMaxExpedtedProfit(int N, vector<int> V, int C, double S) {
	vector<vector<double>> left_over(N+1, vector<double>(N+1, 0));
	vector<vector<double>> dp(N, vector<double>(N+1, -1e9));
	vector<double> maxdp(N+1, -1e9);
	double result = 0;

	// calculate left_over value
	// range [i, j) start at i, end at j-1
	for (int i = 0; i <= N; ++i) {
		for (int j = i+1; j <= N; ++j) {
			left_over[i][j] = (left_over[i][j-1] + V[j-1]) * (1 - S);
		}
	}

	// calculate dp
	// Init position 0
	for (int i = 0; i < N; ++i) 
		dp[i][0] = 0;
	// range j -> i
	// for each new pickup i, try to fit old pickup j
	maxdp[0] = 0;
	for (int i = 1; i <= N; ++i) {
		for (int j = 0; j < i; ++j) {
			// double maxdp = -1e9;
			// // maxdp = max(dp[*][j])
			// for (int k = 0; k <= j; ++k)
			// 	maxdp = max(maxdp, dp[k][j]);

			// double leftofer = 0;
			// // calculate leftover from j to i
			// for (int k = j; k < i-1; ++k) {
			// 	leftofer = (leftofer + V[k]) * (1 - S);
			// }

			// dp[j][i] = max(dp[*][j]) + (Vi - C) + leftover[j][i]
			dp[j][i] = maxdp[j] + V[i-1] - C + left_over[j][i-1];
			maxdp[i] = max(maxdp[i], dp[j][i]);
		}
		result = max(result, maxdp[i]);
	}

	// print dp
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j <= N; ++ j)
			cout << dp[i][j] << '\t';
		cout << endl;
	}

	return result;
}

bool test1() {
	int N = 5;
	vector<int> V{10, 2, 8, 6, 4};
	int C = 5;
	double S = 0.0;
	double expedted = 25.0;
	double actual = getMaxExpedtedProfit(N, V, C, S);
	return abs(expedted - actual) <= epsilon;
}

bool test2() {
	int N = 5;
	vector<int> V{10, 2, 8, 6, 4};
	int C = 5;
	double S = 1.0;
	double expedted = 9.0;
	double actual = getMaxExpedtedProfit(N, V, C, S);
	return abs(expedted - actual) <= epsilon;
}

bool test3() {
	int N = 5;
	vector<int> V{10, 2, 8, 6, 4};
	int C = 3;
	double S = 0.5;
	double expedted = 17.0;
	double actual = getMaxExpedtedProfit(N, V, C, S);
	return abs(expedted - actual) <= epsilon;
}

bool test4() {
	int N = 5;
	vector<int> V{10, 2, 8, 6, 4};
	int C = 3;
	double S = 0.15;
	double expedted = 20.108250;
	double actual = getMaxExpedtedProfit(N, V, C, S);
	return abs(expedted - actual) <= epsilon;
}

bool test5() {
	int N = 1;
	vector<int> V{10};
	int C = 11;
	double S = 0.0;
	double expedted = 0.0;
	double actual = getMaxExpedtedProfit(N, V, C, S);
	return abs(expedted - actual) <= epsilon;
}

int main() {
	cout << test1() << endl;
	cout << test2() << endl;
	cout << test3() << endl;
	cout << test4() << endl;
	cout << test5() << endl;
	return 0;
}