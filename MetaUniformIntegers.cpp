#include <iostream>
#include <algorithm>

using namespace std;
/*
	Find # of uniform number in range [A, B]
	1 <= A <= B <= 1e12
	a number is uniform if all digits are equal
*/
// one digit [1, 9] => {1, 2, 3, 4, 5, 6, 7, 8, 9}
// 2 digits => {11, 22, 33, 44, 55, 66, 77, 88, 99}
// 3 digits => 
// n digits => {1n, 2n, 3n, 4n, 5n, 6n, 7n, 8n, 9n}

void analyzeDigit(long long n, int& countDigit, int& firstDigit) {
	countDigit = 1;
	while (n / 10 != 0) {
		countDigit++;
		n /= 10;
	}
	firstDigit = n;
}

bool is_uniform(long long& n, int& firstDigit, int& countDigit, const long long one[]) {
	return n == firstDigit * one[countDigit - 1];
}

int dumbway(long long A, long long B) {
	int result = 0;
	int firstDigit, countDigit;
	const long long one[12] = {1, 11, 111, 1111, 11111, 111111, 1111111, 11111111, 111111111, 1111111111, 11111111111, 111111111111};
	for (long long i = A; i <= B; ++i) {
		analyzeDigit(i, countDigit, firstDigit);
		if (is_uniform(i, firstDigit, countDigit, one))
			result++;
	}
	return result;
}

int getUniformIntergerCountInInterval(long long A, long long B) {
	const int max_uniform = 9;
	const long long one[13] = {1, 11, 111, 1111, 11111, 111111, 1111111, 11111111, 111111111, 1111111111, 11111111111, 111111111111, 1111111111111};

	int countDigitA, firstDigitA, countDigitB, firstDigitB;
	analyzeDigit(A, countDigitA, firstDigitA);
	analyzeDigit(B, countDigitB, firstDigitB);

	// cout << firstDigitA << ' ' << countDigitA << ' ' << firstDigitA * one[countDigitA - 1] << endl;

	// if A = 12 then let A = 22
	// if A = 21 then let A = 22
	// if A = 98 then let A = 99
	long long temp = firstDigitA * one[countDigitA - 1];
	if (A <= temp) {
		A = temp;
	} else {
		firstDigitA++;
		A = firstDigitA * one[countDigitA - 1];
	}

	// if B = 37 then let B = 33
	// if B = 73 then let B = 66
	temp = firstDigitB * one[countDigitB - 1];
	if (B >= temp) {
		B = temp;
	} else {
		// if 100 then => 99
		firstDigitB--;
		if (firstDigitB == 0) {
			firstDigitB = 9;
			countDigitB--;
		}
		B = firstDigitB * one[countDigitB - 1];
	}

	cout << A << ' ' << B << endl;

	if (A > B)
		return 0;

	int result = 0;
	if (countDigitA == countDigitB) {
		result += firstDigitB - firstDigitA + 1;
	} else {
		result += max_uniform - firstDigitA + 1;
		result += firstDigitB;

		if (countDigitA + 1 < countDigitB) {
			result += max_uniform * (countDigitB - countDigitA - 1);
		}
	}
	
	cout << result << endl;
	return result;
}

bool test1() {
	long long A = 75;
	long long B = 300;
	int expected = 5;
	// {77, 88, 99, 111, 222}
	// leftA = 77
	// rightB = 300
	int actual = getUniformIntergerCountInInterval(A, B);
	return actual == expected;
}

bool test2() {
	long long A = 1;
	long long B = 9;
	int expected = 9;
	// 1, 2, 3, 4, 5, 6, 7, 8, 9
	int actual = getUniformIntergerCountInInterval(A, B);
	return actual == expected;
}

bool test3() {
	long long A = 999999999999;
	long long B = 999999999999;
	int expected = 1;
	int actual = getUniformIntergerCountInInterval(A, B);
	return actual == expected;
}

bool test4() {
	long long A = 12;
	long long B = 3455;
	// left = 22;
	// right = 3333;
	// {22, 33, 44, 55, 66, 77, 88, 99} U {9 numer of 3 digits} U {1111, 2222, 3333}
	int expected = 8 + 9 + 3;
	int actual = getUniformIntergerCountInInterval(A, B);
	return actual == expected;
}

bool test5() {
	long long A = 12;
	long long B = 73;
	// left = 22;
	// right = 66;
	// {22, 33, 44, 55, 66}
	int expected = 5;
	int actual = getUniformIntergerCountInInterval(A, B);
	return actual == expected;
}

bool test6() {
	long long A = 1;
	long long B = 78;
	// left = 1, right = 77;
	// 9 + {11, 22, 33, 44, 55, 66, 77}
	int expected = 9 + 7;
	int actual = getUniformIntergerCountInInterval(A, B);
	return actual == expected;
}

bool test7() {
	long long A = 3;
	long long B = 9 * 111111111111 + 1;
	cout << B << endl;
	int expected = 9 * 12 - 2;
	int actual = getUniformIntergerCountInInterval(A, B);
	return actual == expected;
}

bool test8() {
	long long A = 999999999998;
	long long B = 999999999999;
	int expected = dumbway(A, B);
	int actual = getUniformIntergerCountInInterval(A, B);
	return actual == expected;
}

int main() {
	// cout << "test1: \n" << test1() << endl;
	// cout << "test2: \n" << test2() << endl;
	// cout << "test3: \n" << test3() << endl;
	// cout << "test4: \n" << test4() << endl;
	// cout << "test5: \n" << test5() << endl;
	// cout << "test6: \n" << test6() << endl;
	cout << "test7: \n" << test7() << endl;
	cout << "test8: \n" << test8() << endl;

	// long long one[12] = {1, 11, 111, 1111, 11111, 111111, 1111111, 11111111, 111111111, 1111111111, 11111111111, 111111111111};
	// long long A = 11111 * 4;
	// int firstDigit;
	// int digit;
	// analyzeDigit(A, digit, firstDigit);
	// cout << firstDigit << ' ' << digit << endl;
	// cout << is_uniform(A, firstDigit, digit, one);

	return 0;
}