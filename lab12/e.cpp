#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cmath>
#include <deque>
#include <queue>
#include <cassert>
#include <stack>
#include <iomanip>
#include <utility>
#include <math.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;

ll inf = 9223372036854775807;
ll ans = 0;

struct edge {
    ll s, e, f, a, c, rev, r, n;
};

vector<vector<edge>> g;
ll maxf = 0;
ll n;
bool ford() {
    vector<ll> dist(g.size(), inf);
    vector<edge*> p(g.size(), nullptr);
    dist[0] = 0;
    while (true) {
        int ok = 1;
        for (int j = 0; j < g.size(); j++) {
            for (edge &e : g[j]) {
                if (dist[j] < inf && e.f != e.a) {
                    if (dist[e.e] == inf || dist[e.e] > dist[j] + e.c) {
                        dist[e.e] = dist[j] + e.c;
                        p[e.e] = &e;
                        ok = 0;
                    }
                }
            }
        }
        if (ok) break;
    }
    if (dist[g.size() - 1] == inf) {
        return false;
    }
    vector<edge*> way;
    ll x = g.size() - 1;
    while (p[x] != nullptr) {
        way.push_back(p[x]);
        x = p[x]->s;
    }
    ll mx = inf;
    for (int i = 0; i < way.size(); i++) {
        mx = min(mx, (way[i]->a - way[i]->f));
    }
    maxf += mx;
    for (int i = 0; i < way.size(); i++) {
        way[i]-> f += mx;
        ans += way[i]->c * mx;
        g[way[i] -> e][way[i] -> rev].f -= mx;
    }
    return true;
}
vector<int> used;
bool dfs(ll s, vector<int> &used, vector<ll> &p) {
    used[s] = 1;
    if (s == n) {
        return true;
    }
    for (edge &e : g[s]) {
        if (e.n != -1  && !used[e.e]) {
            if (dfs(e.e, used, p)) {
                p.push_back(e.n);
                if (s != 0) e.n = -1;
                return true;
            }
        }
    }
    return false;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll m, k;
    cin >> n >> m >> k;
    g.resize(n + 1);
    for (int i = 1; i <= m; i++) {
        ll x, y, c; cin >> x >> y >> c;
        g[x].push_back({x, y,0,1,c, (ll) g[y].size(), (ll)g[y].size() + 1,i});
        g[y].push_back({y, x,0,0,-c, (ll) g[x].size() - 1, 0,i});
        g[y].push_back({y, x,0,1,c, (ll) g[x].size(), (ll)g[x].size() - 1,i});
        g[x].push_back({x, y,0,0,-c, (ll) g[y].size() - 1,0,i});
    }
    g[0].push_back({0,1,0,k, 0, (ll) g[1].size(), 0});
    g[1].push_back({1,0,0,0, 0, (ll) g[0].size() - 1, 0});
    while(ford());
    if (maxf < k) {
        cout << -1;
        return 0;
    }
    cout << fixed << setprecision(7) << (double) ans / (double) k <<'\n';
    for (vector<edge> &v : g) {
        for (edge &e : v) {
            if (e.n == -1 || e.s == 0 || e.e == 0) continue;
            if (e.f <= 0) {
                e.n = -1;
            } else {
                auto x = g[e.e][e.r];
                if (e.f >= g[e.e][e.r].f) {
                    e.f -= g[e.e][e.r].f;
                    g[e.e][e.r].f = 0;
                } else {
                    g[e.e][e.r].f -= e.f;
                    e.f = 0;
                }
                if (e.f == 0) e.n = -1;
                if (g[e.e][e.r].f == 0) g[e.e][e.r].n = -1;
            }
        }
    }
    for (int i = 0; i < k; i++) {
        used.assign(n + 1, 0);
        vector<ll> p;
        dfs(0, used, p);
        cout << p.size() - 1 << ' ';
        for (int j = (int)p.size() - 2; j >= 0; j--) cout << p[j] << ' ';
        cout << '\n';
    }
}