#include <bits/stdc++.h>
#define N 200005

using namespace std;

typedef long long ll;
vector<int> r[11];
int n, k, len[N];
long long ans, p[11], a[N];

int main()
{
    freopen("1029D.INP","r",stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n >> k;
    for(int i = 1; i <= n; ++i)
    {
        cin >> a[i];
        int x = a[i];
        while(x != 0)
        {
            len[i]++;
            x /= 10;
        }
        r[len[i]].push_back(a[i]%k);
    }

    p[1] = 10;
    for(int i = 2; i <= 10; ++i) p[i] = (p[i-1]*10)%k;
    for(int i = 1; i <= 10; ++i)
        sort(r[i].begin(), r[i].end());

    for(int i = 1; i <= n; ++i)
    {
        for(int j = 1; j <= 10; ++j)
        {
            int t1 = (a[i]%k * p[j]) %k;
            int t2 = (k-t1)%k;
            int leg = lower_bound(r[j].begin(), r[j].end(), t2) - r[j].begin(),
                rig = upper_bound(r[j].begin(), r[j].end(), t2) - r[j].begin();
            ans += (ll)rig - (ll)leg;
            if(len[i]==j && (t1+ a[i]%k )%k==0) ans--;
        }
    }

    cout << ans;
    return 0;
}
