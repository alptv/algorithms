#include <iostream>

using namespace std;

const int MAXN = (int)2e5 + 10;

int dp_lca[MAXN][100];
int dp_min[MAXN][100];
int depth[MAXN];

int n;
const int root = 1;
int LOG = 0;
int m;


int LCA(int v1, int v2) {
    if (depth[v1] < depth[v2]) swap(v1,v2);

    for (int i = LOG; i >= 0; i--){
        if (depth[v1] - depth[v2] < (1 << i)) continue;
        v1 = dp_lca[v1][i];
    }
    if (v1 == v2) return v1;
    for (int i = LOG; i >= 0; i--){
        if (dp_lca[v1][i] == dp_lca[v2][i]) continue;
        v1 = dp_lca[v1][i];
        v2 = dp_lca[v2][i];
    }
    return dp_lca[v1][0];
}

int MIN(int v, int lca) {
    int ans = INT32_MAX;
    for (int i = LOG; i >= 0; i--){
        if (depth[v] - depth[lca] <(1 << i)) continue;
        ans = min(ans,dp_min[v][i]);
        v = dp_lca[v][i];
    }
    return ans;
}





int main() {
    freopen("minonpath.in", "r", stdin);
    freopen("minonpath.out", "w", stdout);
    cin >> n;
    int tmp = 1;
    while (tmp <= n) {
        tmp *= 2;
        LOG++;
    }

    depth[1] = 0;
    for (int i = 2; i <= n; i++){
        cin >> dp_lca[i][0];
        cin >> dp_min[i][0];
        depth[i] = depth[dp_lca[i][0]] + 1;

    }
    dp_lca[root][0] = root;


    for (int i = 1; i <= LOG; i++) {
        for (int v = 1; v <=n; v++) {
            dp_lca[v][i] = dp_lca[dp_lca[v][i - 1]][i - 1];
            dp_min[v][i] = min(dp_min[dp_lca[v][i - 1]][i - 1], dp_min[v][i - 1]);
        }
    }
    cin >> m;
    int v1, v2;
    for (int i = 0; i < m; i++){
        cin >> v1 >> v2;
        int lca = LCA(v1, v2);
        cout << min(MIN(v1, lca), MIN(v2, lca)) << '\n';
    }
}