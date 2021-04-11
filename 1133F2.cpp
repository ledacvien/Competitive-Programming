#include <bits/stdc++.h>
#define N 200005

using namespace std;
vector<int> a[N], g[N];
queue<int> Q;
int n, m, D, deg[N];

void bfs()
{
    memset(deg, 0, sizeof(deg));
    Q.push(1); deg[0] = deg[1] = 1;
    while(Q.size())
    {
        int u = Q.front(); Q.pop();
        for(auto v : g[u]) if(!deg[v]){
            deg[v] = 1; Q.push(v);
            a[u].push_back(v);
        }
    }
}

int main()
{
    freopen("1133F2.INP","r",stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n >> m >> D;
    while(m--){
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
        deg[u]++; deg[v]++;
    }

    if(deg[1] < D){
        cout << "NO"; return 0;
    }

    sort(g[1].begin(), g[1].end(), [](int a, int b){
         return deg[a] < deg[b];
    });
    for(int i = 0; i < g[1].size()-D; ++i){
        int v = --deg[g[1][i]];
        g[1][i] = 0;
        if(!v){ cout << "NO"; return 0; }
    }
    bfs();

    memset(deg, 0, sizeof(deg));
    for(int u = 1; u <= n; ++u) if(a[u].size()){
        deg[u] = 1;
        for(auto v : a[u]) deg[v] = 1;
    }
    for(int i = 1; i <= n; ++i)
        if(!deg[i]){ cout << "NO"; return 0; }

    cout << "YES\n";
    for(int u = 1; u <= n; ++u)
        if(a[u].size()) for(auto v : a[u])
            cout << u << ' ' << v << '\n';
    return 0;
}
