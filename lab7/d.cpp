#include <vector>
#include <iostream>
#include <cmath>
#include <set>
#include <stack>

using namespace std;


set <pair <int,int>> edges;

multiset <pair<int,int>> all;

vector <vector <int>> g;
vector<bool> used;
vector<int> ans;
vector<int> d;
vector<int> in;


vector <vector <int>> nG;


int min(int a, int b) {
    return a > b ? b : a;
}


int count = 0;
int t = 0;

void dfs(int v, int p) {
    used[v] = true;
    in[v] = t++;
    d[v] = in[v];
    for (int u : g[v]) {
        if (u == p) continue;
        if (used[u]) {
            d[v] = min(d[v], in[u]);
        } else {
            dfs(u, v);
            d[v] = min(d[u],d[v]);
        }
    }
    if (p !=-1 && in[p] < d[v]){
        int x = min(p, v); int y = p > v ? p : v;
        if (all.count({x , y}) == 1) {
            edges.insert({v, p});
            edges.insert({p, v});
        }
    }
}


void dfs2(int v) {
    ans[v] = count;
    for (int u : nG[v]) {
        if (ans[u] == -1) {
            dfs2(u);
        }
    }
}



int main(){
    int n, m;
    cin >> n >> m;

    used.assign(n, false);
    g.assign(n, {});
    d.assign(n,-1);
    in.assign(n, -1);
    ans.assign(n,-1);
    nG.assign(n, {});

    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        if (x > y) swap(x, y);
        all.insert({x - 1, y - 1});
        if (all.count({x - 1, y - 1}) == 1) {
            g[x - 1].push_back(y - 1);
            g[y - 1].push_back(x - 1);
        }
    }
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs(i, -1);
        }
    }
    for (int v = 0; v < n; v ++) {
        for (int e = 0; e < g[v].size(); e++) {
            if (!edges.count({v, g[v][e]})) {
                nG[v].push_back(g[v][e]);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (ans[i] == -1) {
            count++;
            dfs2(i);
        }
    }
    cout << count << endl;
    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }


}