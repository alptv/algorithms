#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;


int costs[1005][1005];


void timeIn(int v, vector<bool> &used, vector<int> &tin, vector<vector<int>> &g_out){
    used[v] = true;
    for (int u: g_out[v]) {
        if (!used[u]) {
            timeIn(u, used, tin, g_out);
        }
    }
    tin.push_back(v);
}

void dfs(int v, vector<bool> &used, vector<vector<int>> &g_in) {
    used[v] = true;
    for (int u : g_in[v]) {
        if (!used[u]) {
            dfs(u, used, g_in);
        }
    }
}

bool isStrongConnected(vector <vector<int>> &g_in, vector <vector<int>> &g_out,int n) {
    vector <bool> used(n, false);
    vector <int> tin;
    for (int v = 0; v < n; v++) {
        if (!used[v])
        timeIn(v, used, tin, g_out);
    }
    int v = tin[n - 1];
    used.assign(n, false);
    dfs(v, used, g_in);
    return !any_of(used.begin(), used.end(), [](bool a) { return !a;});
}


int binSearch(int l, int r, int n) {
    while (l < r - 1) {
        int m = (l + r) / 2;
        vector <vector<int>> g_in(n);
        vector <vector<int>> g_out(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++){
                if (costs[i][j] <= m) {
                    g_out[i].push_back(j);
                    g_in[j].push_back(i);
                }
            }
        }
        if (isStrongConnected(g_in, g_out, n)) {
            r = m;
        } else {
            l = m;
        }
    }
    return r;
}

int main() {
    freopen("avia.in", "r", stdin);
    freopen("avia.out", "w", stdout);
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; ++j) {
            cin >> costs[i][j];
        }
    }
    cout << binSearch(-1, 1000000001, n);

}