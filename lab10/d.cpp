#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cmath>
#include <deque>
#include <queue>
#include <cassert>
#include <iomanip>
#include <fstream>


using namespace std;
#define pb push_back
#define pf push_front
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;

vector<vi> g;
vector<int> used;
vector<int> usedL;
vector<int> usedR;
vector<int> p;
int c = 0;



bool dfs(int v) {
    used[v] = c;
    for (int u : g[v]) {
        if (p[u] == -1) {
            p[u] = v;
            return  true;
        }
        if (used[p[u]] != c && dfs(p[u])) {
            p[u] = v;
            return true;
        }
    }
    return false;
}

void dfs2(int v) {
    usedL[v] = 1;
    for (int u : g[v]) {
        if (!usedR[u]) {
            usedR[u] = 1;
            if (p[u] != -1 && !usedL[p[u]]) {
                dfs2(p[u]);
            }
        }
    }
}





void solve() {
    int n, m;
    cin >> n >> m;
    g.assign(n, {});
    p.assign(m, -1);
    used.assign(n, -1);
    for (int i = 0; i < n; i++) {
        int x;
        vector<int> c(m + 1, 1);
        while (true) {
            cin >> x;
            if (x == 0) break;
            c[x] = 0;
        }
        for (int j = 1; j < m + 1; j++) {
            if (c[j])
            g[i].pb(j - 1);
        }
    }
    for (int i = 0; i < n; i++) {
        dfs(i);
        c++;
    }

    usedL.assign(n, 0);
    usedR.assign(m, 0);

    vector<int> free(n, 1);
    for (int i = 0; i < m; i++) {
  //      cout << p[i] << " p\n";
        if (p[i] != -1) free[p[i]] = 0;
    }
    for (int i = 0; i < n; i++) {
        if (free[i] && !usedL[i]) {
            dfs2(i);
        }
    }
    int boys = 0, girls = 0;
    for (int x : usedL) if (x) boys++;
    for (int x : usedR) if (!x) girls++;
    cout << boys + girls << '\n';
    cout << boys << ' ' << girls << '\n';
    for (int i = 0; i < n; i++) if (usedL[i]) cout << i + 1<< ' ';
    cout << '\n';
    for (int i = 0; i < m; i++) if (!usedR[i]) cout << i + 1<< ' ';
    cout << "\n\n";

}





int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("birthday.in", "r", stdin);
    freopen("birthday.out", "w", stdout);
    int tt; cin >> tt;
    while (tt--) {
        solve();
        c = 0;
    }
}