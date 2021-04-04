#include <bits/stdc++.h>
#define N 100005

using namespace std;
int n, m;
bool lazy[4*N];
long long a[N], st[4*N];

void build(int i, int l, int r)
{
    if(l == r){
        st[i] = a[l];
        return;
    }
    int m = (l+r)>>1;
    build(i<<1, l, m);
    build((i<<1)+1, m+1, r);
    st[i] = max(st[i<<1], st[(i<<1)+1]);
}

void down(int i)
{
    if(lazy[i] == 0) return;
    st[i<<1] = st[i];
    lazy[i<<1] = lazy[i];
    st[(i<<1)+1] = st[i];
    lazy[(i<<1)+1] = lazy[i];
    lazy[i] = 0;
}

void update(int i, int l, int r, int d, int c, long long val)
{
    if(l > c || r < d) return;
    if(l >= d && r <= c){
        st[i] = val;
        lazy[i] = 1;
        return;
    }
    down(i); int m = (l+r)>>1;
    update(i<<1, l, m, d, c, val);
    update((i<<1)+1, m+1, r, d, c, val);
    st[i] = max(st[i<<1], st[(i<<1)+1]);
}

long long get(int i, int l, int r, int d, int c)
{
    if(l > c || r < d) return -1;
    if(l >= d && r <= c) return st[i];
    down(i); int m = (l+r)>>1;
    return max(get(i<<1, l, m, d, c), get((i<<1)+1, m+1, r, d, c));
}

int main()
{
    freopen("272C.INP","r",stdin);
    freopen("272C.OUT","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n;
    for(int i = 1; i <= n; ++i) cin >> a[i];
    build(1, 1, n);

    cin >> m;
    while(m--){
        int w; long long h;
        cin >> w >> h;
        long long ma = get(1, 1, n, 1, w);
        cout << ma << '\n';
        update(1, 1, n, 1, w, ma + h);
    }
    return 0;
}
