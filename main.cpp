#include <bits/stdc++.h>
#define N 300005
#define t first
#define b second

using namespace std;

typedef long long ll;
typedef pair<ll, ll> ii;

ii s[N];
priority_queue<ll, vector<ll>, greater<ll> > pq;
int n, k;
ll ans, sum;

int main()
{
    freopen("1140C.INO","r",stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n >> k;
    for(int i = 1; i <= n; ++i) cin >> s[i].t >> s[i].b;

    sort(s+1, s+n+1, [](ii a, ii b){ return a.b > b.b; });
    for(int i = 1; i <= n; ++i)
    {
        sum += s[i].t; pq.push(s[i].t);
        while(pq.size() > k){
            sum -= pq.top(); pq.pop();
        }
        ans = max(ans, sum * s[i].b);
    }

    cout << ans;
    return 0;
}
