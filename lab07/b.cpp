#include <vector>
#include <iostream>
#include <cmath>
#include <set>

using namespace std;

set <pair <int,int>>  s;

vector <pair <int,int>> edges;

int count = 0;


vector <vector <int>> g;

vector<bool> used;

vector<int> d;

vector<int> in;


int min(int a, int b) {
    return a > b ? b : a;
}


int time = 0;

void dfs(int v, int p) {
    used[v] = true;
    in[v] = time++;
    d[v] = in[v];
    for (int u : g[v]) {
        if (p == u) continue;
        if (used[u]) {
            d[v] = min(d[v], in[u]);
        } else {
            dfs(u, v);
            d[v] = min(d[v], d[u]);
        }
    }
    if (p !=-1  && d[v] > in[p]){
        count++;
        s.insert({v, p});
        s.insert({p,v});
    }
}

int main(){
    int n, m;
    cin >> n >> m;

    used.assign(n, false);
    g.assign(n, {});
    d.assign(n, -1);
    in.assign(n, -1);


    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        edges.emplace_back(x - 1, y - 1);
        g[x - 1].push_back(y - 1);
        g[y - 1].push_back(x - 1);

    }
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs(i, -1);
        }
    }
    cout << count << "\n";

    for (int i = 0; i < m; i++) {
        if (s.count(edges[i])) {
            cout << i + 1 << ' ';
        }
    }



}