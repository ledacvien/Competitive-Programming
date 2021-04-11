#include <iostream>
#define N 2003
#define mod 1000000007

using namespace std;
int n, k, ans, dp[N][N];

int main()
{
    freopen("414B.INP","r",stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n >> k;
    for(int i = 1; i <= n; ++i) dp[1][i] = 1;
    for(int i = 2; i <= k; ++i)
        for(int j = 1; j <= n; ++j)
            for(int k = 1; k*k <= j; ++k)
                if(j%k == 0){
                    dp[i][j] = (dp[i][j] + dp[i-1][k]) % mod;
                    if(j/k != k)
                        dp[i][j] = (dp[i][j] + dp[i-1][j/k]) % mod;
                }
    for(int i = 1; i <= n; ++i) ans = (ans + dp[k][i]) % mod;
    cout << ans;
    return 0;
}
