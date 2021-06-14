#include <iostream>
#include <vector>
#include <map>


using namespace std;

vector<vector<int>> g;
vector<bool> used;
vector<int> grandi;
vector<int> need;

void dfs(int v) {
    used[v] = true;
    for (int u : g[v]) {
        if (!used[u]) {
            dfs(u);
            if (grandi[v] == -1) {
                grandi[v] = grandi[u] + 1;
            } else {
                grandi[v] = grandi[v]^(grandi[u] + 1);
            }
        }
    }
    if (grandi[v] == -1) grandi[v] = 0;
}

int e = -1;
map<pair<int,int>, int> edges;

void dfs2(int v) {
    if (e != -1)
        return;
    used[v] = true;
    for (int u: g[v]) {
        if (!used[u] && (e == -1)) {
            need[u] = need[v]^(grandi[v]^(grandi[u] + 1));
            need[u]--;
            int without = grandi[v]^(grandi[u] + 1);
            if (without == need[v]) {
                e = edges[{v, u}];
                return;
            }
            dfs2(u);
        }
    }
}



int main() {
    int n, s;
    cin >> n >> s;
    s--;
    g.assign(n, {});
    used.assign(n, false);
    grandi.assign(n, -1);
    need.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int x, y; cin >> x >> y;
        x--; y--;
        g[x].push_back(y);
        g[y].push_back(x);
        edges[{x,y}] = i + 1;
        edges[{y, x}] = i + 1;
    }
    dfs(s);
    if (!grandi[s]) {
        cout << 2;
    } else {
        cout << 1 << endl;
        need[s] = 0;
        used.assign(n , false);
        dfs2(s);
        cout << e;
    }

}