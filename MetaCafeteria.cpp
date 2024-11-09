#include <bits/stdc++.h>
using namespace std;
// Write any include statements here

long long getMaxAdditionalDinersCount(long long N, long long K, int M, vector<long long> S) {
    long long result = 0;
    long long left, right, range;
    // one seat will take a block size of 2K+1
    long long block = K + 1;

    cout << "getMaxAdditionalDinersCount\n";

    sort(S.begin(), S.end());

    // Handle index 0
    right = max(1LL * 1, S[0] - K - 1);
    if (right > 1) {
        result += right / block;
        if (right % block != 0)
            result++;
        cout << right << ' ' << result << endl;
    }

    for (int i = 1; i < M; ++i)
    {
        right = max(1LL * 1, S[i] - K);
        left = min(N, S[i-1] + K);
        range = right - left - 1;
        if (range > 0) {
            result += range / block;
            if (range % block != 0)
                result++;
        }

        cout << left << ' ' << right << ' ' << range << ' ' << result << endl;
    }
    // Handle index M-1
    left = S[M-1] + K;
    range = N - left;
    if (range > 0) {
        result += range / block;
            if (range % block != 0)
                result++;
        cout << left << ' ' << range << ' ' << result << endl;
    }

    cout << "END\n\n";
    return result;
}

long long test1() {
    long long N = 10;
    long long K = 1;
    int M = 2;
    vector<long long> S{2, 6};
    return getMaxAdditionalDinersCount(N, K, M, S);   
}

long long test2() {
    long long N = 15;
    long long K = 2;
    int M = 3;
    // 1 2 3 4 5 {6} 7 8 9 10 {11} 12 13 {14} 15
    vector<long long> S{11, 6, 14};
    return getMaxAdditionalDinersCount(N, K, M, S);
}

long long test3() {
    long long N = 10;
    long long K = 2;
    int M = 1;
    // {1} 2 3 {4} 5 6 {7} 8 9 {10} 11 12 {13} 14
    vector<long long> S{1};
    return getMaxAdditionalDinersCount(N, K, M, S);
}

int main() {
    cout << test1() << endl;
    cout << test2() << endl;
    cout << test3() << endl;
    return 0;
}