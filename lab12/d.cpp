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
    ll s, e, f, a, c, rev;
};

vector<vector<edge>> g;

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
    for (int i = 0; i < way.size(); i++) {
        way[i]-> f += mx;
        ans += way[i]->c * mx;
        g[way[i] -> e][way[i] -> rev].f -= mx;
    }
    return true;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    g.resize(2 * n + 2);
    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        int j = i + 1;
        g[j].push_back({j, n + j, 0, inf, x, (ll) g[n + j].size()});
        g[n + j].push_back({n + j, j, 0, 0, -x, (ll) g[j].size() - 1});
        g[n + j].push_back({n + j, j, 0 , inf , 0, (ll)g[j].size()});
        g[j].push_back({j, n + j, 0, 0, 0, (ll) g[n + j].size() - 1});
        g[0].push_back({0, j, 0, 1, 0, (ll)g[j].size()});
        g[j].push_back({j, 0, 0, 0, 0, (ll)g[0].size() - 1});
        g[n + j].push_back({n + j, 2 * n + 1, 0, 1, 0, (ll)g[2 * n + 1].size()});
        g[2 * n + 1].push_back({2 * n + 1, n + j, 0, 0, 0, (ll)g[j].size() - 1});
    }
    while (m--) {
        ll x, y, c; cin >> x >> y >> c;
        g[x].push_back({x, n + y, 0, inf, c, (ll)g[n + y].size()});
        g[y + n].push_back({n + y, x, 0, 0, -c, (ll)g[x].size() - 1});
    }
    while(ford());
    cout << ans;
}