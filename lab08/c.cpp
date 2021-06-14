#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

const int INF = (int)1e9;


vector<vector<pair<int,int>>> g;



int main() {
    int n;
    cin >> n;
    int t;
    g.assign(n + 1, {});
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> t;
            if (t != 100000) {
                g[j].emplace_back(i, t);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        g[i].emplace_back(0, 0);
    }
    vector<int> p(n + 1, - 1);
    vector<int> d(n + 1, INF);
    d[0] = 0;
    int w = -1;
    for (int k = 1; k <= n + 1; k++) {
        for (int v = 0; v <= n; v++) {
            for (auto u : g[v]) {
                //  cout << " d[v]: " << d[v] << " u.sec: " << u.second << endl;
                if (d[v] > d[u.first] + u.second) {
                    if (k == n + 1) {
                        w = v;
                    }
                    //    cout << "u: " << u.first << " v: " << v  << " k: " << k << endl;
                    d[v] = d[u.first] + u.second;
                    p[v] = u.first;
                }
            }
        }
    }
    if (w == - 1) {
        cout << "NO";
        return 0;
    }
    cout << "YES\n";
    for (int i = 1; i <= n; i++) {
        w = p[w];
    }
    vector <int> ans;
    int start = w;
    ans.push_back(w);
    w = p[w];
    while (start != w) {
        ans.push_back(w);
        w = p[w];
    }
    reverse(ans.begin(), ans.end());
    cout << ans.size() << '\n';
    for (int v : ans) {
        cout << v << " ";
    }
}