#include <iostream>
#include <map>
#include <vector>


using namespace std;

int min(int a,int b) {
    return a > b ? b : a;
}
const int MAXN = 20050;

bool used[MAXN];
bool used2[MAXN];
int pr[MAXN];
int d[MAXN];
int in[MAXN];
map<pair<int,int>, int> comp;
vector <pair<int,int>> edges;



vector <vector <int>> g;

int t = 0;
int count  = 1;

void calc(int v, int p) {
    used[v] = true;
    in[v] = t++;
    d[v] = in[v];
    pr[v] = p;
    for (int u : g[v]) {
        if (u == p) continue;
        if (used[u]) {
            d[v] = min(d[v], in[u]);
        } else {
            calc(u, v);
            d[v] = min(d[v], d[u]);
        }
    }
}

void dfs(int v , int p) {
    used2[v] = true;

    for (int u : g[v]) {
        if (p == -1) {
            if (!used2[u]) {
                comp[{v, u}] = count;
                comp[{u, v}] = count++;
                dfs(u, v);
            }
            continue;
        }
        if (u == p) continue;
        if (used2[u] && in[u] < in[v] && pr[v] != u) {
            comp[{v, u}] = comp[{p, v}];
            comp[{u, v}] = comp[{p, v}];
            continue;
        }
        if (!used2[u]) {
            if (d[u] <= in[p]) {
                comp[{u, v}] = comp[{p, v}];
                comp[{v, u}] = comp[{p, v}];
                dfs(u, v);
            } else {
                comp[{u, v}] = count;
                comp[{v, u}] = count++;
                dfs(u, v);
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    g.assign(n, {});
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        g[x - 1].push_back(y - 1);
        g[y - 1].push_back(x - 1);
        edges.emplace_back(x - 1, y - 1);
    }
    for (int i = 0; i < n; i++) {
        if (!used[i])
        calc(i, -1);
    }
    for (int i = 0; i < n; i++) {
        if (!used2[i])
        dfs(i, -1);
    }
    cout << count - 1  << endl;
    for (int i = 0; i < m; ++i) {
        cout << comp[edges[i]] << " ";
    }
}


 