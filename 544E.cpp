#include <bits/stdc++.h>
#define N 5003

using namespace std;
int n, k, ans, a[N], cnt[N], dp[N][N];

int main()
{
    freopen("544E.INP", "r", stdin);
    ios_base::sync_with_stdio(false);

    cin >> n >> k;
    for(int i = 1; i <= n; ++i) cin >> a[i];

    sort(a+1, a+n+1);
    memset(cnt, 1, sizeof cnt);
    for(int j = 1, i = 1; i <= n; ++i)
    {
        while(j <= i){
            if(a[i] - a[j] <= 5){
                cnt[i] = i-j+1;
                break;
            }
            j++;
        }
    }

    ans = 0;
    memset(dp, 0, sizeof(dp));
    for(int i = 1; i <= n; ++i)
    {
        for(int j = 1; j <= k; ++j)
        {
            dp[i][j] = max(dp[i-1][j], dp[i-cnt[i]][j-1] + cnt[i]);
            ans = max(dp[i][j], ans);
        }
    }

    cout << ans;
    return 0;
}
