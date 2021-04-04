#include <iostream>

using namespace std;
int S, len, p, mi, sum, a[10], ans[1000006];

int main()
{
    freopen("349B.INP","r",stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> S; mi = 10000000;
    for(int i = 1; i <= 9; ++i)
    {
        cin >> a[i];
        if(mi >= a[i]){
            mi = a[i]; p = i;
        }
    }

    len = S/mi; sum = len*mi;
    for(int i = 1; i <= len; ++i) ans[i] = p;

    for(int i = 9, j = 1; i > p; --i)
    {
        while(sum + (a[i]-a[p]) <= S)
        {
            sum += a[i]-a[p];
            ans[j] = i; j++;
        }
    }

    if(len == 0) cout << "-1";
    for(int i = 1; i <= len; ++i) cout << ans[i];
    return 0;
}
