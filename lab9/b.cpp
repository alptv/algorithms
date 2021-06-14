#include <iostream>
#include <vector>


using  namespace std;


int main() {
    string s;
    cin >> s;
    vector<int> p(s.size());
    p[0] = 0;
    for (int i = 1; i < s.size(); i++) {
        int pref = p[i - 1];
        while (pref > 0 && s[pref] != s[i]) {
            pref = p[pref - 1];
        }
        if (s[pref] == s[i]) p[i] = pref + 1;
        else p[i] = pref;
    }
    for (int x : p) cout << x << " ";
}