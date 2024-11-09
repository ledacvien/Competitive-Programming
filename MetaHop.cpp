#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long getSecondsRequired(long long N, int F, vector<long long> P) {
	long long mini = 1e12;
	for (auto x : P) mini = min(mini, x);
	return N - mini;
}

bool test1() {
	long long N = 3;
	int F = 1;
	vector<long long> P{1};
	int expected = 2;
	long long actual = getSecondsRequired(N, F, P);
	return expected == actual;
}

bool test2() {
	long long N = 6;
	int F = 3;
	vector<long long> P{5, 2, 4};
	// {2, 4, 5} 6
	int expected = 4;
	long long actual = getSecondsRequired(N, F, P);
	return expected == actual;
}

bool test3() {
	long long N = 14;
	int F = 7;
	vector<long long> P{1, 2, 4, 5, 6, 10, 13};
	int expected = 36;
	long long actual = getSecondsRequired(N, F, P);
	return expected == actual;
}


int main() {
	cout << test1() << endl;
	cout << test2() << endl;
	cout << test3() << endl;
	return 0;
}