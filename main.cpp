#include <bits/stdc++.h>
#define N 100005

using namespace std;
int n, x[N], h[N], dp[N][3];

int main()
{
    freopen("545C.INP","r",stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n;
    for(int i = 1; i <= n; ++i) cin >> x[i] >> h[i];

    // 0 : fall back    1 : stand    2 : fall front
    x[0] = h[0] = -1e9; x[n+1] = 2e9+7;
    for(int i = 1; i <= n; ++i)
    {
        // fall back
        if(x[i]-h[i] > x[i-1]+h[i-1]) dp[i][0] = dp[i-1][2]+1;
        if(x[i]-h[i] > x[i-1]) dp[i][0] = max(dp[i][0], max(dp[i-1][1], dp[i-1][0])+1 );
        // stand
        if(x[i] > x[i-1]+h[i-1]) dp[i][1] = dp[i-1][2];
        dp[i][1] = max(dp[i][1], max(dp[i-1][0], dp[i-1][1]));
        // fall front
        if(x[i]+h[i] < x[i+1]){
            dp[i][2] = max(dp[i-1][0], dp[i-1][1])+1;
            if(x[i] > x[i-1]+h[i-1]) dp[i][2] = max(dp[i][2], dp[i-1][2]+1);
        }
    }

    for(int i = 1; i <= 3; ++i){
        for(int j = 1; j <= n; ++j) cout << dp[j][i] << ' ';
        cout << '\n';
    }

    cout << max(dp[n][0], max(dp[n][1], dp[n][2]));
    return 0;
}
