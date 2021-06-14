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

int mtr[105][105];

vector<vi> g;
vector<int> used;
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





int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("dominoes.in", "r", stdin);
    freopen("dominoes.out", "w", stdout);
    int n, m,a,b;
    cin >> n >> m;
    cin >> a >> b;
    int count = 0;
    int cn = 0;
    vector<int> biek(n * m, -1);
    int next = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c; cin >> c;
            if ((i + j) % 2 != 0) cn++;
            else {
                biek[m * i + j] = next++;
            }
            if (c == '*') {
                mtr[i][j] = 1;
                count++;
            }
        }
    }
    g.assign(cn, {});
    p.assign(n * m - cn, -1);
    used.assign(cn, -1);
    if (2 * b <= a) {
        cout << b * count;
        return 0;
    }
    next = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!mtr[i][j] || (i + j) % 2 == 0) continue;
            if (j < m - 1 && mtr[i][j + 1]) {
                g[next].pb(biek[(m * i + j + 1)]);
            }
            if (j > 0 && mtr[i][j - 1]) {
                g[next].pb(biek[(m * i + j - 1)]);
            }
            if (i < n - 1 && mtr[i + 1][j]){
                g[next].pb(biek[(m * (i + 1) + j)]);
            }
            if (i > 0 && mtr[i - 1][j]) {
                g[next].pb(biek[(m * (i - 1) + j)]);
            }
            next++;
        }
    }

    for (int i = 0; i < cn; i++){
        dfs(i);
        c++;
    }
    int cp = 0;
    for (int x : p) cp += (x >= 0) ? 1 : 0;
    cout << cp * a + (count - 2 * cp) * b;

}