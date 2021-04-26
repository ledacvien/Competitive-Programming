#include <bits/stdc++.h>
#define N 200005
#define oo 1000000000000000000

using namespace std;
long long n, H, t, ma, sum, ans, a[N];

int main()
{
    freopen("1141E.INP","r",stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> H >> n;
    for(int i = 1; i <= n; ++i) cin >> a[i];

    t = H; ma = oo;
    for(int i = 1; i <= n; ++i){
        t += a[i]; sum += a[i];
        if(t <= 0){
            cout << i; return 0;
        }
        ma = min(ma, sum);
    }

    if(sum >= 0){ cout << "-1"; return 0; }

    ans = (H + ma) / (-sum);
    H += sum * ans;
    ans *= n;

    for(int i = 1;; ++i){
        if(i % n == 0) H += a[n];
        else H += a[i%n];
        ans++;
        if(H <= 0){
            cout << ans; return 0;
        }
    }
    return 0;
}
