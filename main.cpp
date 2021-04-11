#include <bits/stdc++.h>

using namespace std;

int main()
{
    string s; cin >> s;
    for(int i = 0; i < s.size(); ++i) s[i] = char(s[i]-48);

    /*if(s.size() < 3){
        if(s[0]%8 == 0) cout << "YES\n" << (int)s[0];
        else if(s.size() > 1){
            if(s[1]%8 == 0) cout << "YES\n" << (int)s[1];
            else{
                if((s[0]*10 + s[1])%8 == 0)
                    cout << "YES\n" << (int)s[0] << (int)s[1];
                else if((s[1]*10 + s[0])%8 == 0)
                    cout << "YES\n" << (int)s[1] << (int)s[0];
                else cout << "NO";
            }
        }
        else cout << "NO";
        return 0;
    }*/

    for(int i = 0; i < s.size(); ++i)
    {
        if(s[i] == '0' || s[i]%8 == 0)
            { cout << "YES\n" << (int)s[i]; return 0; }

        for(int j = i+1; j < s.size(); ++j)
        {
            if((s[i]*10 + s[j])%8 == 0)
            {
                cout << "YES\n" << (int)s[i] << (int)s[j];
                return 0;            }

            for(int k = j+1; k < s.size(); ++k)
            {
                int t = s[i]*100 + s[j]*10 + s[k];
                if(t%8 == 0){
                    cout << "YES\n";
                    if(s[i] != '0'){
                        cout << (int)s[i] << (int)s[j] << (int)s[k];
                    }
                    else{
                        if(s[j] != '0'){
                            cout << (int)s[j] << (int)s[k];
                        }
                        else cout << (int)s[k];
                    }
                    return 0;
                }
            }
        }
    }
    cout << "NO";
    return 0;
}
