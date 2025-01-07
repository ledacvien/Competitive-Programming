#include <bits/stdc++.h>

using namespace std;

/*
	There are N competitors, each trying to independently solve same set of problems
	Each problems has either 1pt or 2pts
	1 <= N <= 5e5
	1 <= Si <= 1e9

	For each Si, find possible pair Xi * 1 + Yi * 2 = Si and Xi + Yi is minimal
	For all pairs (Xi, Yi), find pair (Xi, Yi) that Xi and Yi is max

	Solution: For each Si, be greedy and maximize Yi

	// 2 3 5
 	[2, 1, 2]
*/

// Easy version: Possible points: 1, 2
int getMinProblemCount(int N, vector<int> S) {
	// int result = 0;
	int Xi_max = 0, Yi_max = 0;

	for (int i = 0; i < N; ++i) {
		int Yi = S[i] / 2;
		int Xi = S[i] - 2 * Yi;

		Xi_max = max(Xi, Xi_max);
		Yi_max = max(Yi, Yi_max);
	}

	return Xi_max + Yi_max;
}

// easy ver
bool test1() {
	int N = 6;
	vector<int> S{1, 2, 3, 4, 5, 6};
	int expected = 4;
	int actual = getMinProblemCount(N, S);
	return expected == actual;
}

// easy ver
bool test2() {
	int N = 4;
	vector<int> S{4, 3, 3, 4};
	int expected = 3;
	int actual = getMinProblemCount(N, S);
	return expected == actual;
}

// easy ver
bool test3() {
	int N = 4;
	vector<int> S{2, 4, 6, 8};
	int expected = 4;
	int actual = getMinProblemCount(N, S);
	return expected == actual;
}

// Hard version: Possible points: 1, 2, 3
int getMinProblemCountH(int N, vector<int> S) {
	// count mod0, mod1, mod2
	int cnt[3] = {0, 0, 0};
	int max_S = -1, max_S2 = -1;
	int hasOne = 0;

	for (auto num : S) {
		if (max_S < num) {
			max_S2 = max_S;
			max_S = num;
		}
		// check for mod1 and mod2
		if (num % 3 != 0) {
			cnt[num % 3] = 1;
		}
		if (num == 1) {
			hasOne = 1;
		}
	}
	// maximize number of 3
	cnt[0] = max_S / 3;
	// Reduce.
	// Case 1: if we have 1, 2, then we can take out one 3
	if (max_S % 3 == 0 && cnt[1] && cnt[2]){
		cnt[0]--;
		return cnt[0] + cnt[1] + cnt[2];
	}
	// Case 2: if we don't have score single 1, and we have 2, 
	//   then try take out 3, 1 by adding 2 with one 2 we already have 
	else if (max_S % 3 == 1 && max_S - 1 != max_S2 && hasOne == 0 && cnt[1] && cnt[2]) {
		cnt[2]++;
		cnt[1]--;
		cnt[0]--;
	}

	cout << "mod0\tmod1\tmod2\n";
	cout << cnt[0] << '\t' << cnt[1] << '\t' << cnt[2] << endl;
	return cnt[0] + cnt[1] + cnt[2];
}

bool test1H() {
	int N = 5;
	vector<int> S{1, 2, 3, 4, 5};
	int expected = 3;
	int actual = getMinProblemCountH(N, S);
	cout << "test1H: " << actual << endl;
	return expected == actual;
}

bool test2H() {
	int N = 4;
	vector<int> S{4, 3, 3, 4};
	// [1, 3]
	int expected = 2;
	int actual = getMinProblemCountH(N, S);
	cout << "test2H: " << actual << endl;
	return expected == actual;
}

bool test3H() {
	int N = 3;
	vector<int> S{1, 2, 6};
	// [1, 2, 3]
	int expected = 3;
	int actual = getMinProblemCountH(N, S);
	cout << "test3H: " << actual << endl;
	return expected == actual;
}

bool test4H() {
	int N = 5;
	vector<int> S{2, 4, 7}; 
	// [2, 2, 3]
	// [3, 3, 1, 2] => [3, 2, 2]
	int expected = 3;
	int actual = getMinProblemCountH(N, S);
	cout << "test4H: " << actual << endl;
	return expected == actual;
}

bool test5H() {
	int N = 3;
	vector<int> S{2, 4, 6};
	// [3, 3, 1, 2] => [3, 1, 2]
	int expected = 3;
	int actual = getMinProblemCountH(N, S);
	cout << "test5H: " << actual << endl;
	return expected == actual;
}

bool test6H() {
	int N = 4;
	vector<int> S{2, 4, 6, 7};
	// [3, 2, 2, 2]
	// [3, 2, 2]
	int expected = 4;
	int actual = getMinProblemCountH(N, S);
	cout << "test6H: " << actual << endl;
	return expected == actual;
}


int main() {
	cout << test1H() << endl;
	cout << test2H() << endl;
	cout << test3H() << endl;
	cout << test4H() << endl;
	cout << test5H() << endl;
	cout << test6H() << endl;
	return 0;
}