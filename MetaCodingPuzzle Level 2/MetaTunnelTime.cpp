#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;

/*
	Tunnel Time
	There's a circular train track with a circumference of C metres. Positions along the 
	 track are measured in metres, clockwise from its topmost point. For ex, the topmost point
	 is position 0. 1 metre clockwise along the track is position 1, and 1 metre ccw along 
	 the track is position C - 1.
	There are N tunnels, each start at Ai and ends at Bi. No tunnel touches position 0, and 
	 no overlap tunnels. K is tunnel time.
	Requirement: calculate total time the train travel before tunnel time reach K.
	3 <= C <= 1e12
	1 <= N <= 5e5
	1 <= Ai < Bi <= C-1
	1 <= K <= 1e12

	Algo: Greedy
		calculate total tunnel_time
		calculate the total time where the train goes full cycle.
		greedily move the train until K is met.
*/

long long getSecondsElapsed(long long C, int N, vector<long long> A, vector<long long> B, long long K) {
	long long result = 0;
	long long tunnel_time = 0;
	vector<pair<long long, long long>> tunnel(N);

	for (int i = 0; i < N; ++i) {
		tunnel_time += B[i] - A[i];
		tunnel[i] = {A[i], B[i]};
	}

	if (K >= tunnel_time) {
		// if K is a multiple of tunnel_time, then we could go a full cycle 
		//	instead of the amount we need. Check testcase 3
		if (K % tunnel_time == 0) {
			result += (K / tunnel_time - 1) * C;
			K = tunnel_time;
		} else {
			result += (K / tunnel_time) * C;
			K = K % tunnel_time;
		}
	}

	sort(tunnel.begin(), tunnel.end());
	long long pre = 0;
	for (pair<long long, long long> p : tunnel) {
		printf("%lld - %lld = %lld\n", p.second, p.first, p.second - p.first);
		if (p.second - p.first <= K) {
			result += p.second - pre;
			pre = p.second;
			K -= p.second - p.first;
		} else {
			result += p.first - pre + K;
			K = 0;
		}

		if (K == 0) {
			break;
		}
		cout << result << ' ' << K << endl;
	}

	return result;
}

bool test1() {
	int C = 10;
	int N = 2;
	vector<long long> A{1, 6};
	vector<long long> B{3, 7};
	int K = 7;
	int expected = 22;
	int actual = getSecondsElapsed(C, N, A, B, K);
	cout << actual << endl;
	return actual == expected;
}

bool test2() {
	int C = 50;
	int N = 3;
	vector<long long> A{39, 19, 28};
	vector<long long> B{49, 27, 35};
	int K = 15;
	int expected = 35;
	int actual = getSecondsElapsed(C, N, A, B, K);
	cout << actual << endl;
	return actual == expected;
}

bool test3() {
	int C = 10;
	int N = 2;
	vector<long long> A{1, 6};
	vector<long long> B{3, 7};
	int K = 6;
	int expected = 17;
	int actual = getSecondsElapsed(C, N, A, B, K);
	cout << actual << endl;
	return actual == expected;
}

int main() {
	cout << test1() << endl << endl;
	cout << test2() << endl << endl;
	cout << test3() << endl << endl;
}