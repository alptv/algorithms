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
    int n, m;
    cin >> n >> m;
    g.assign(n, {});
    used.assign(n, -1);
    p.assign(m, -1);
    for (int i = 0; i < n; i++) {
        int x = -1;
        while (x != 0) {
            cin >> x;
            if (x != 0) g[i].pb(x - 1);
        }
    }
    for (int i = 0; i < n; i++){
        dfs(i);
        c++;
    }
    int ans = 0;
    for (int x : p) ans += (x >= 0) ? 1 : 0;
    cout << ans << '\n';
    for (int i = 0; i < m; i++) {
        if (p[i] != -1) {
            cout << p[i] + 1 << " " << i + 1 << '\n';
        }
    }


}