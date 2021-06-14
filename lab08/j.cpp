#include <iostream>
#include <vector>
#include <set>


using namespace std;


vector<vector<int>> g;


vector<bool> used;
vector<int> tp;

void top_sort(int v) {
    used[v] = true;
    for (int u : g[v]) {
        if (!used[u]) {
            top_sort(u);
        }
    }
    tp.push_back(v);
}


int main() {
    int n, m;
    cin >> n >> m;
    g.assign(n, {});
    used.assign(n, false);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y; x--; y--;
        g[x].push_back(y);
    }
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            top_sort(i);
        }
    }
    vector <int> grandi(n, -1);
    for (int i = 0; i < n; i++) {
        if (g[tp[i]].empty()) {
            grandi[tp[i]] = 0;
        } else {
            set<int> set;
            for (int u : g[tp[i]]) {
                set.insert(grandi[u]);
            }
            int max = *set.end();
            for (int j = 0; j <= max + 1; j++) {
                if (set.count(j) == 0) {
                    grandi[tp[i]] = j;
                    break;
                }
            }
        }
    }
    for (int u : grandi) {
        cout << u << "\n";
    }


}