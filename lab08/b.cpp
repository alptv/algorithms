#include <iostream>
#include <vector>
#include <set>

using namespace std;

const int MAXN = 105;
const int INF = (int)10e15;


int min(int a, int b) {
    return a > b ? b : a;
}

vector <vector <pair<int,int >>> g_out;

int main() {
    int n, m;
    cin >> n >> m;
    g_out.assign(n, {});
    for (int i = 0; i < m; i++) {
        int u, v, c; cin >> u >> v >> c; u--; v--;
        g_out[u].push_back({v, c});
        g_out[v].push_back({u,c});
    }

    vector <long long> d(n, INF);
    d[0] = 0;
    set <pair<long long,int>> minimum;
    minimum.insert({0, 0});
    for (int i = 1; i < n; i++) minimum.insert({INF, i});

    for (int i = 0; i < n ; i++) {
         int v = (*minimum.begin()).second;
         minimum.erase(minimum.begin());
         for (auto u : g_out[v]) {
             if (d[u.first] > d[v] + u.second) {
                 minimum.erase({d[u.first], u.first});
                 minimum.insert({d[v] + u.second, u.first});
                 d[u.first] = d[v] + u.second;
             }
         }
    }
    for (int i = 0; i < n; i++) {
        cout << d[i] << " ";
    }

}