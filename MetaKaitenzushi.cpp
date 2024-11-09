#include <bits/stdc++.h>

using namespace std;

/*
	There are N dishes, each of Di type. 
	You're very hungry, but you'd also like to keep things interesting. The N dishes will arrive 
	in front of you, one after another in order, and for each one you'll eat it as long as it isn't 
	the same type as any of the previous K dishes you've eaten.
*/

int getMaxiumEatenDishCount(int N, vector<int> D, int K) {
	int result = 0;
	set<int> dish_set;
	queue<int> dish_queue;
	dish_set.clear();
	// dish_queue.clear();

	int j = 0;
	for (int i = 0; i < N; ++i)
	{
		// Keeping sliding window K size
		if (dish_queue.size() > K) {
			int top = dish_queue.front();
			dish_queue.pop();
			dish_set.erase(top);
		}
		// New dish
		if (dish_set.find(D[i]) == dish_set.end()) {
			dish_set.insert(D[i]);
			dish_queue.push(D[i]);
			result++;
		}
	}

	return result;
}

bool test1() {
	int N = 6, K = 1;
	vector<int> D{1, 2, 3, 3, 2, 1};
	int expected = 5;
	int actual = getMaxiumEatenDishCount(N, D, K);
	cout << "test1: " << actual << endl;
	return actual == expected;
}

bool test2() {
	int N = 6, K = 2;
	vector<int> D{1, 2, 3, 3, 2, 1};
	int expected = 4;
	int actual = getMaxiumEatenDishCount(N, D, K);
	cout << "test2: " << actual << endl;
	return actual == expected;
}

bool test3() {
	int N = 7, K = 2;
	vector<int> D{1, 2, 1, 2, 1, 2, 1};
	int expected = 2;
	int actual = getMaxiumEatenDishCount(N, D, K);
	cout << "test3: " << actual << endl;
	return actual == expected;
}

int main() {
	cout << test1() << endl;
	cout << test2() << endl;
	cout << test3() << endl;
	return 0;
}