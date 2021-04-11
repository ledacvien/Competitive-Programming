#include <bits/stdc++.h>
#define N 200005

using namespace std;
vector<int> in, de;
int n, a[N], mark[N];
bool ok = true;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n;
    for(int i = 1; i <= n; ++i){
        cin >> a[i]; mark[a[i]]++;
        if(mark[a[i]] > 2) ok = false;
    }

    if(!ok) { cout << "NO"; return 0; }

    sort(a+1, a+n+1);
    for(int i = 1; i <= n; ++i)
    {
        if(mark[a[i]] == 1) in.push_back(a[i]);
        else{ mark[a[i]]--; de.push_back(a[i]); }
    }
    reverse(de.begin(), de.end());

    cout << "YES\n" << in.size() << '\n';
    for(auto i : in) cout << i << ' ';
    cout << '\n' << de.size() << '\n';
    for(auto i : de) cout << i << ' ';
    return 0;
}
