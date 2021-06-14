#include <iostream>
#include <vector>


using namespace std;

const long long INF = 6000 * (long long)1e15;
struct edge {
    int s;
    int e;
    int w;

    edge(int s_, int e_, int w_) {
        s = s_;
        e = e_;
        w = w_;
    }

};

long long d[2005][2005];


long long min(long long a, long long b) {
    if (a > b) return b;
    return  a;
}

vector <edge> edges;
vector<vector<pair<int, long long>>> g;

vector <bool> used;
void dfs(int v) {
    used[v] = true;
    for (auto u : g[v]) {
        if (!used[u.first]) {
            dfs(u.first);
        }
    }
}

int main() {
    int n, m, s;
    cin >> n >> m >> s;
    s--;
    used.assign(n, false);
    g.assign(n, {});
    for (int i = 0; i < m; i++) {
        int st, e;
        long long w;
        cin >> st >> e >> w;
        st--; e--;
        edges.emplace_back(st, e , w);
        g[st].emplace_back(e, w);

    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            d[i][j] = INF;
        }
    }
    d[s][0] = 0;

    vector <int> cycles;
    for (int k = 1; k <= n; k++) {
	for (int i = 0; i < n; i++) {
            d[i][k] = d[i][k - 1];
        }
        for (int v = 0;  v < n; v++) {
            if (d[v][k - 1] == INF) continue;
            for (auto u : g[v]) {
                if (d[u.first][k] > d[v][k - 1] + u.second) {
                    if (k == n) {
                        cycles.push_back(u.first);
                    }
                    d[u.first][k] = d[v][k - 1] + u.second;
             
                }
            }
        }
    }
    vector <long long> ans(n, INF);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ans[i] = min(ans[i], d[i][j]);
        }
    }

    for (int v : cycles) {
        if (!used[v]) {
            dfs(v);
        }
    }
    for (int v = 0; v < n; v++) {
        if (used[v]) {
            cout << "-\n";
            continue;
        }
        if (ans[v] == INF) {
            cout << "*\n";
            continue;
        }
        cout << ans[v] << '\n';
    }


}