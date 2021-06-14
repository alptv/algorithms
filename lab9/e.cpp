#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <deque>
#include <algorithm>

using namespace std;




int main() {
    string s;
    cin >> s;
    vector<int> p(s.size(), 0);
    for (int i = 1; i < s.size(); i++) {
        int pref = p[i - 1];
        while (pref > 0 && s[pref] != s[i]) {
            pref = p[pref - 1];
        }
        p[i] = pref;
        if (s[pref] == s[i]) p[i]++;
    }
    int ans = s.size() - p[s.size() - 1];
    while (s.size() % ans != 0) ans++;
    cout << ans;


}