#include <vector>
#include <iostream>
#include <cmath>
#include <set>
#include <algorithm>

using namespace std;


vector <pair <int,int>> edges;

int count = 0;


vector <vector <int>> g;

vector<bool> used;

vector<int> d;

vector<int> in;

vector <int> ans;


int min(int a, int b) {
    return a > b ? b : a;
}


int time = 0;

void dfs(int v, int p) {
    used[v] = true;
    in[v] = time++;
    d[v] = in[v];
    int child = 0;
    bool is = true;
    for (int u : g[v]) {
        if (u == p) continue;
        if (used[u]) {
            d[v] = min(d[v], in[u]);
        } else {
            dfs(u, v);
            child++;
            d[v] = min(d[v], d[u]);
            if (p != -1 && d[u] > in[p]) {
                is = false;
            }
        }
    }
    if  (!is && p != -1) {
        ans.push_back(v);
    }
    if (p == -1 && child > 1) {
        ans.push_back(v);
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
    sort(ans.begin(), ans.end());

    cout << ans.size() << '\n';
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] + 1<< ' ';
    }


}