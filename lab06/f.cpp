#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 100005;

const int LOG = 20;

int TREE_SIZE;

int ROOT = 0;

vector<int> tree[MAXN];

int dp[MAXN][LOG + 1];

int depth[MAXN];

int tOut[MAXN];

int tOutRev[MAXN];

int out = 0;


void dfs(int v , int d) {
    depth[v] = d;
    for (int child : tree[v]) {
        dfs(child, d + 1);
    }
    tOutRev[out] = v;
    tOut[v] = out++;
}

void buildDp() {
    for (int i = 1; i <= LOG; i++){
        for (int v = 0; v < TREE_SIZE; v++) {
            dp[v][i] = dp[dp[v][i - 1]][i - 1];
        }
    }
}

int getLCA(int v1, int v2) {
    if (depth[v1] < depth[v2]) swap(v1, v2);

    for (int i =  LOG; i >=0; i--){
        if (depth[v1] - depth[v2] >=(1 << i)) {
            v1 = dp[v1][i];
        }
    }
    if (v1 == v2) return v2;

    for (int i = LOG; i >=0; i--) {
        if (dp[v1][i] == dp[v2][i]) continue;
        v1= dp[v1][i];
        v2 = dp[v2][i];
    }
    return dp[v1][0];
}




int main() {
    scanf("%d", &TREE_SIZE);
    int g = 0;
    for (int i = 0; i < TREE_SIZE; i++){
        cin >> dp[i][0];
        if (dp[i][0] == -1) {
            dp[i][0] = i;
            ROOT = i;
        } else {
            dp[i][0]--;
            tree[dp[i][0]].push_back(i);
        }
    }
    scanf("%d", &g);
    dfs(ROOT, 1);
    buildDp();
    int k;
    for (int i = 0; i < g; i++) {
        scanf("%d", &k);
        if (k == 0) {
            cout << 0 << endl;
            continue;
        }
        vector<int> group;
        for (int j = 0; j < k; j++) {
            int tmp;
            scanf("%d", &tmp);
            tmp--;
            group.push_back(tOut[tmp]);
        }
        sort(group.begin(), group.end());
        int ans = 0;
        ans += depth[tOutRev[group[0]]];
        for (int j = 1; j < k; j++) {
            int lca = getLCA(tOutRev[group[j - 1]], tOutRev[group[j]]);
            if (lca == tOutRev[group[j]]) continue;
            ans += depth[tOutRev[group[j]]] - depth[lca];
        }
        printf("%d\n", ans);
    }
}