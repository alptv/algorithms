#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 250000 + 10;

int parents[MAXN];

int dp[MAXN][100];

int depth[MAXN];

int n;

vector <int> tree[MAXN];


void dfs(int v, int d) {
    depth[v] = d;
    for (int child : tree[v]) {
        dfs(child, d + 1);
    }
}

int LCA(int v1, int v2) {
    if (depth[v1] < depth[v2]) {
        swap(v1, v2);
    }
    int h = depth[v1] - depth[v2];
    int pow = 1;
    int c = 0;
    while (pow <= n) {
        c++;
        pow <<= 1;
    }
    for (int i = c; i >= 0; i--) {
        if ((1 << i) > h) continue;
        h -= (1 << i);
        v1 = dp[v1][i];
    }
    if (v1 == v2) return v1;

    for (int i = c; i >= 0; i--) {
        if (dp[v1][i] == 0 || dp[v2][i] == 0) continue;
        if (dp[v1][i] == dp[v2][i]) continue;
        v1 = dp[v1][i];
        v2 = dp[v2][i];
    }
 //   cout << v1;
    return parents[v1];
}



int main() {
    cin >> n;
    int root = 1;
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        tree[p].push_back(i + 1);
        parents[i + 1] = p;
    }
    dp[root][0] = root;

    for (int i = 1; i <= n; i++) {
        dp[i][0] = parents[i];
    }

    for (int i = 1; (1 << i) <= n; i++) {
        for (int v = 1; v <= n; v++) {
            dp[v][i] = dp[dp[v][i - 1]][i - 1];
        }
    }
    dfs(root, 0);
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int v1, v2;
        cin >> v1 >> v2;
        cout << LCA(v1, v2) << '\n';
    }

}