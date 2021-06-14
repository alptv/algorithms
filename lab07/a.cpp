#include <iostream>
#include <vector>
#include <queue>

using namespace std;






int main() {
    int n,m;
    cin >> n >> m;

    vector <int> inp(n,0);
    vector <vector <int>> g(n);

    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        inp[y - 1]++;
        g[x - 1].push_back(y - 1);
    }
    queue <int> zeroes;

    for (int i = 0; i < n; i++) {
        if (inp[i] == 0) {
            zeroes.push(i);
        }
    }
    vector <int> ans;
    for (int i = 0; i < n; i++) {
        if (zeroes.empty()) {
            cout << -1;
            return 0;
        }
        int v = zeroes.front();
        zeroes.pop();
        ans.push_back(v);
        for (int u : g[v]) {
            inp[u]--;
            if (!inp[u]) {
                zeroes.push(u);
            }
        }
    }
    for (int i = 0; i < n; i++){
        cout << ans[i] + 1 << " ";
    }



}