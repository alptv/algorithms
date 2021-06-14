#include <iostream>
#include <vector>


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
    freopen("game.out", "w", stdout);
    freopen("game.in", "r", stdin);
    int n, m, s;
    cin >> n >> m >> s;
    s--;
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
    vector <int> win(n, 0);
    win[tp[0]] = 2;
    for (int i = 0; i < n; i++) {
        win[tp[i]] = 2;
        for (int u : g[tp[i]]) {
            if (win[u] == 2) {
                win[tp[i]] = 1;
                break;
            }
        }
    }
    if (win[s] == 1) {
        cout << "First player wins";
    } else {
        cout << "Second player wins";
    }


}