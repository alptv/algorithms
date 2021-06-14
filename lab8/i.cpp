#include <iostream>
#include <vector>
#include <set>
#include <queue>


using namespace std;






int main() {
    int n, m;
    while (cin >> n && cin>> m) {
        vector<int> used(n, -1);
        vector<vector<pair<int, int>>> g_in(n);
        vector<vector<pair<int, int>>> g_out(n);
        for (int i = 0; i < m; i++) {
            int x, y;
            cin >> x >> y;
            x--;
            y--;
            g_out[x].emplace_back(y, 0);
            g_in[y].emplace_back(x, 0);
        }
        queue<pair<int, int>> q;
        for (int i = 0; i < n; i++) {
            if (g_out[i].empty()) {
                used[i] = 0;
                q.push({i, 0});
            }
        }
        vector<int> counts(n, 0);
        while (!q.empty()) {
            auto p = q.front();
            q.pop();
            int v = p.first;
            int isWin = p.second;
            if (!isWin) {
                for (auto &u : g_in[v]) {
                    if (used[u.first] != -1) continue;
                    used[u.first] = 1;
                    q.push({u.first, 1});
                }
            } else {
                for (auto &u : g_in[v]) {
                    u.second++;
                    counts[u.first]++;
                    if (used[u.first] != -1) continue;
                    if (counts[u.first] == g_out[u.first].size()) {
                        used[u.first] = 0;
                        q.push({u.first, 0});
                    }
                }
            }
        }
        for (int i = 0; i < n; i++) {
            if (used[i] == -1) {
                cout << "DRAW\n";
            }
            if (used[i] == 1) {
                cout << "FIRST\n";
            }
            if (used[i] == 0) {
                cout << "SECOND\n";
            }
        }
        cout << '\n';
    }

}