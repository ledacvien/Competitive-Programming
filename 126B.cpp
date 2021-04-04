#include <bits/stdc++.h>
#define N 1000006
#define base1 31
#define base2 29
#define mod 100000007 //1e8+7

using namespace std;

typedef long long ll;
typedef struct data{
    int len;
    long long h1, h2;
};

vector<data> sub;
ll p1[N], p2[N], hash1[N], hash2[N];
int n;
string s;

void input()
{
    cin >> s; n = s.size(); s = '1'+s;
    for(int i = 1; i <= n; ++i)
    {
        hash1[i] = (hash1[i-1]*base1 + s[i]-'a'+1) % mod;
        hash2[i] = (hash2[i-1]*base2 + s[i]-'a'+1) % mod;
    }
    p1[0] = p2[0] = 1;
    for(int i = 1; i <= n; ++i)
    {
        p1[i] = (p1[i-1]*base1) % mod;
        p2[i] = (p2[i-1]*base2) % mod;
    }
}

ll get1(int i, int j)
{
    return (hash1[j] - hash1[i-1]*p1[j-i+1] + mod*mod) % mod;
}
ll get2(int i, int j)
{
    return (hash2[j] - hash2[i-1]*p2[j-i+1] + mod*mod) % mod;
}

void process()
{
    for(int i = 1; i <= n-2; ++i)
    {
        ll t1 = get1(1, i),
           t2 = get2(1, i),
           j1 = get1(n-i+1, n),
           j2 = get2(n-i+1, n);
        if(t1==j1 && t2==j2) sub.push_back({i, t1, t2});
    }

    sort(sub.begin(), sub.end(), [](data a, data b){
        return a.len > b.len; });

    for(auto i : sub)
    {
        for(int j = 2; j <= n-i.len; ++j)
        {
            ll t1 = get1(j, j+i.len-1),
               t2 = get2(j, j+i.len-1);
            if(t1==i.h1 && t2==i.h2){
                for(int k = j; k <= j+i.len-1; ++k) cout << s[k];
                return;
            }
        }
    }
    cout << "Just a legend";
}

int main()
{
    freopen("126B.INP","r",stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    input();
    process();
    return 0;
}
