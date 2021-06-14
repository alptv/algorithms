#include <iostream>

using namespace std;

const int MAXN = (int)2e5 + 10;

int dp_lca[MAXN][25];
int depth[MAXN];

int DSU[MAXN];

int getDSU(int v) {
    if (v == DSU[v])
        return v;
    return DSU[v] = getDSU(DSU[v]);
}


int n;
const int root = 1;
int LOG = 20;


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


int main() {
    cin >> n;
    char c;

    depth[1] = 0;
    dp_lca[root][0] = root;

    DSU[root] = root;
    int number = 2;

    for (int i = 0; i < n; i++) {
        cin >> c;
        if (c == '+') {
            int anc; cin >> anc;
            DSU[number] = number;
            dp_lca[number][0] = anc;
            depth[number] = depth[anc] + 1;
            for (int j = 1; j <= LOG; j++) dp_lca[number][j] = dp_lca[dp_lca[number][j - 1]][j - 1];
            number++;
        }
        if (c == '-') {
            int v; cin >> v;
            DSU[v] = dp_lca[v][0];
        }
        if (c == '?') {
            int v1, v2;
            cin >> v1 >> v2;
            int lca = LCA(v1, v2);
            cout << getDSU(lca) << '\n';
        }
    }

}