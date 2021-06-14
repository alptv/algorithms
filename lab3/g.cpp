#include <bits/stdc++.h>
using namespace std;
int str[105];
int ans[105][105];
int inf = 2000000000;
int arr[105][105];
string rest[105][105];
string s;


bool check(string s, int l, int r) {
    return (s[l] == '{' && s[r] == '}' || s[l] =='[' && s[r] ==']' || s[l] =='(' && s[r] ==')');
}

void restore_answer(string s, int l, int r) {
    if (l-r ==0) return;
    if (ans[l][r] == 0 ){
    for (int i = l; i <= r; i++) {
        cout << s[i];
    }
    return;
    }
    else {
        if (arr[l][r] == -inf) {
            cout << s[l];
            restore_answer(s,l+1,r-1);
            cout << s[r];
        } else {
            restore_answer(s,l,arr[l][r]);
            restore_answer(s,arr[l][r] + 1, r);
        }
    }
}



int main ()
{
    int deleted = 0;
    cin >> s;
    int n = s.size();
    for (int l = n-1; l >= 0; l--) {
        for (int r = l; r < n; r++) {
            if (l==r) {
                ans[l][r] = 1;
                continue;
            }
            int result = inf;
            if (check(s,l,r)) {
                result = ans[l + 1][r - 1];
                rest[l][r] = rest[l+1][r-1];
                arr[l][r] = -inf;
            }
            for (int i = l; i < r; i++) {
                if ((ans[l][i] + ans[i + 1][r]) < result) {
                    result = ans[l][i] + ans[i + 1][r];
                    arr[l][r] = i;
                }
            }
            ans[l][r] = result;
        }
    }
    restore_answer(s,0,n-1);
    }

