#include <vector>
#include <iostream>

using namespace std;

/*
	There's a stack of N inflatable discs, with ith disc from the top having radius Ri inches
	Stack is unstable if disc on top is >= to disc bottom.
	Find minimum disc that need deflated for stack to be stable
*/

// Easy ver: 1 <= N <= 50
//			1 <= Ri <= 1e9

int getMinimumDeflatedDisCount(int N, vector<int> R) {
	// At the very least, stable stack look like
	//  {1, 2, 3, .., N}
	if (R[N-1] < N)
		return -1;
	if (N == 1)
		return 0;

	int result = 0;

	for (int i = N-2; i >= 0; --i) {
		if (R[i] >= R[i+1]) {
			result++;
			R[i] = R[i+1] - 1;
		}

		if (R[i] == 0) 
			return -1;
	}

	return result;
}


bool test1() {
	int N = 5;
	vector<int> R{2, 5, 3, 6, 5};
	int expected = 3;
	int actual = getMinimumDeflatedDisCount(N, R);
	return actual == expected;
}

bool test2() {
	int N = 3;
	vector<int> R{100, 100, 100};
	int expected = 2;
	int actual = getMinimumDeflatedDisCount(N, R);
	return actual == expected;
}

bool test3() {
	int N = 4;
	vector<int> R{6, 5, 4, 3};
	int expected = -1;
	int actual = getMinimumDeflatedDisCount(N, R);
	return actual == expected;
}

int main() {
	cout << test1() << endl;
	cout << test2() << endl;
	cout << test3() << endl;
	return 0;
}