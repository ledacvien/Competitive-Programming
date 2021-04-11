/*#include <iostream>
#include <vector>
#define N 200005

using namespace std;
vector<int> g[N];
int n, hmax, ans, h[N];

void dfs(int u, int p)
{
    h[u] = h[p]+1;
    hmax = max(hmax, h[u]);
    for(auto v : g[u])
        if(v != p) dfs(v,u);
}

int main()
{
    freopen("1029E.INP","r",stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n;
    for(int i = 0; i < n-1; ++i)
    {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    h[0] = -1; dfs(1,0);

    if(hmax>3 && hmax%3 == 2) ans++;
    for(int i = 2; i <= n; ++i)
        if(h[i]>=3 && h[i]%3 == 0) ans++;

    cout << ans;
    return 0;
}*/
#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    string s; bool ok1 = 0, ok2 = 0;

    cin >> s;
    for(int i = 0; i < s.size()-1; ++i)
        if(s[i] == 'A' && s[i+1] == 'B' && !ok1) ok1 = 1, i++;
        else if(s[i] == 'B' && s[i+1] == 'A' && !ok2) ok2 = 1, i++;
    cout << ((ok1 && ok2) ? "YES" : "NO");
    return 0;
}
