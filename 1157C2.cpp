#include <bits/stdc++.h>
#define N 200005

using namespace std;
struct{
    int v; char c;
} b[N];
vector<int> d, c;
int n, m, a[N], ok[2] = {1,1};

int main()
{
    freopen("1157C2.INP","r",stdin);
    freopen("1157C2.OUT","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n; a[0] = a[n+1] = 0;
    for(int i = 1; i <= n; ++i) cin >> a[i];

    for(int i = 1; i <= n; ++i)
        if(a[i-1] < a[i]) d.push_back(a[i]); else break;
    for(int i = n; i > 0; --i)
        if(a[i+1] < a[i]) c.push_back(a[i]); else break;

    d.push_back(N-1); c.push_back(N);
    for(int i = 0, j = 0; i < d.size() && j < c.size();){
        if(d[i] < c[j] && ok[0])     { b[m++] = {d[i],'L'}; i++; }
        else if(d[i] > c[j] && ok[1]){ b[m++] = {c[j],'R'}; j++; }
        else if(ok[0] && ok[1]){
            int ii = i+1, jj = j+1;
            while(d[ii] == c[jj] && ii < d.size() && jj < c.size()){
                ii++; jj++;
            }
            if(d.size()-ii > c.size()-jj){
                for(;i < ii; ++i) b[m++] = {d[i],'L'};
                ok[1] = 0; j++;
            }
            else{
                for(;j < jj; ++j) b[m++] = {c[j],'R'};
                ok[0] = 0; i++;
            }
        }
        else{
            while(ok[0] && i < d.size()){ b[m++] = {d[i],'L'}; i++; }
            while(ok[1] && j < c.size()){ b[m++] = {c[j],'R'}; j++; }
        }
    }

    for(int i = m-1; i >= 0; --i)
        if(b[i].v == N-1 || b[i].v == N) m--;
    cout << m << '\n';
    for(int i = 0; i < m; ++i) cout << b[i].c;
    return 0;
}
