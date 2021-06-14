#include <vector>
#include <iostream>

using namespace std;

struct edge {
    int s;
    int e;
    long long w;
    edge(int s_, int e_, long long w_) {
        s = s_;
        e = e_;
        w = w_;
    }
};

const long long MAX_LONG = 9223372036854775806;


void check(int v, vector<bool> &used, vector<vector<int>> &g) {
    used[v] = true;
    for (int u : g[v]) {
        if (!used[u]) {
            check(u, used, g);
        }
    }
}

bool dfs(int v, vector<edge> &edges, int n) {
    vector<bool> used(n, false);
    vector<vector<int>> g(n);
    for (edge e : edges) {
        g[e.s].push_back(e.e);
    }
    check(v, used, g);
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            return false;
        }
    }
    return true;
}

void timeIn(int v, vector<bool> &used, vector<int> &tin, vector<vector<int>> &g_out){
    used[v] = true;
    for (int u: g_out[v]) {
        if (!used[u]) {
            timeIn(u, used, tin, g_out);
        }
    }
    tin.push_back(v);
}

void getComp(int v, vector<int> &comp, vector<vector<int>> &g_in, int count) {
    comp[v] = count;
    for (int u : g_in[v]) {
        if (comp[u] == - 1) {
            getComp(u, comp, g_in, count);
        }
    }
}

pair <vector<int>, int> condensation(vector <edge> edges, int n){
    vector<vector<int>> g_in(n);
    vector<vector<int>> g_out(n);
    for (edge e : edges){
        g_out[e.s].push_back(e.e);
        g_in[e.e].push_back(e.s);
    }
    vector<bool> used(n,false);
    vector <int> tin;
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            timeIn(i, used, tin, g_out);
        }
    }
    int count = 0;
    vector<int> comp(n, -1);
    for (int i = n - 1; i >= 0; i--) {
        if (comp[tin[i]] == - 1) {
            getComp(tin[i], comp, g_in, count++);
        }
    }
    return {comp, count};
}

long long ans;

void find(int root, int n, vector <edge> &edges) {
    vector<long long> minimum(n, MAX_LONG);
    for (edge e : edges) {
        minimum[e.e] = min(e.w, minimum[e.e]);
    }
    vector <edge> zero;
    for (edge e : edges) {
        if (minimum[e.e] == e.w) {
            zero.push_back(e);
        }
    }
    for (int v = 0; v < n; v++) {
        if (v != root) {
            ans += minimum[v];
        }
    }
    if (dfs(root, zero, n)) {
        return;
    }
    pair <vector <int>, int> comp = condensation(zero, n);
    vector <edge> nedges;
    vector<vector<int>> g(n, {-1});
    for (edge e : edges) {
        if (comp.first[e.s] != comp.first[e.e]) {
            nedges.emplace_back(comp.first[e.s], comp.first[e.e], e.w - minimum[e.e]);
        }
    }
    find(comp.first[root], comp.second, nedges);
}

int main() {
    int n, m;
    cin >> n >> m;
    vector <edge> edges;
    for (int i = 0; i < m; i++) {
        int s, e ,w;
        cin >> s >> e >> w;
        edges.emplace_back(s - 1, e - 1 , w);
    }
    if (!dfs(0, edges, n)) {
        cout << "NO";
    } else {
        cout << "YES\n";
        find(0, n, edges);
        cout << ans;
    }

}