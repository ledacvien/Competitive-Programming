#include <bits/stdc++.h>
#define N 100005

using namespace std;
struct data{
    int x, h, p;
} a[N];
int n, x[N], kq[N], st[4*N];

void update(int id, int l, int r, int p, int v)
{
    if(l>p || r<p) return;
    if(l==p && l==r){
        st[id] = v;
        return;
    }
    int m = (l+r)>>1;
    update(id<<1, l, m, p, v);
    update((id<<1)+1, m+1, r, p, v);
    st[id] = max(st[id<<1], st[(id<<1)+1]);
}

int getmax(int id, int l, int r, int d, int c)
{
    if(l>c || r<d) return 0;
    if(l>=d && r<=c) return st[id];
    int m = (l+r)>>1;
    return max(getmax((id<<1), l, m, d, c),
               getmax((id<<1)+1, m+1, r, d, c));
}

int main()
{
    freopen("56E.INP","r",stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n;
    for(int i = 1; i <= n; ++i)
    {
        cin >> a[i].x >> a[i].h;
        a[i].p = i;
        a[i].h = a[i].x + a[i].h - 1;
    }

    sort(a+1, a+n+1, [](data a, data b){ return a.x < b.x; });

    for(int i = n; i >= 1; --i)
    {
        x[i] = a[i].x;
        int pos = upper_bound(x+i+1, x+n+1, a[i].h) - x - 1;
        int t = getmax(1, 1, n, i+1, pos);

        if(t < i) t = i;
        kq[a[i].p] = t-i+1;
        update(1, 1, n, i, t);
    }

    for(int i = 1; i <= n; ++i) cout << kq[i] << ' ';
    return 0;
}
