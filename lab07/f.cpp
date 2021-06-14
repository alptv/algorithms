#include <iostream>
#include <vector>
#include <set>
using namespace std;

const int MAXN = 10005;
vector <vector<int>> g_in;
vector <vector<int>> g_out;
vector <int> tin;

bool used[MAXN];
int in[MAXN];
int comp[MAXN];

int t = 0;

void timeIn(int v){
    used[v] = true;
    for (int u: g_out[v]) {
        if (!used[u]) {
            timeIn(u);
        }
    }
    tin.push_back(v);
}

void dfs(int v, int component) {
    comp[v] = component;
    for (int u : g_in[v]) {
        if (comp[u] == 0) {
            comp[u] = component;
            dfs(u, component);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    g_in.assign(n, {});
    g_out.assign(n, {});
    for (int i = 0;i < m; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        g_out[x].push_back(y);
        g_in[y].push_back(x);
    }
    for (int v = 0; v < n; v++) {
        if (!used[v]) {
            timeIn(v);
        }
    }
    int count = 1;
    for (int v = n - 1; v >= 0; v--) {
        if (comp[tin[v]] == 0) {
            dfs(tin[v], count++);
        }
    }
    set <pair<int,int>> edges;
    for (int v = 0; v < n; v++) {
        for (int u : g_out[v]) {
            int c1, c2;
            c1 = comp[v];
            c2 = comp[u];
            if (c1 != c2) {
                edges.insert({c1,c2});
                edges.insert({c2 ,c1});
            }
        }
    }
    cout << edges.size() / 2;
}