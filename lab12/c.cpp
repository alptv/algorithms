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

ll inf = (ll) 1e10;
ll ans = 0;

struct edge {
    ll s, e, f, a, c, rev;
};

vector<vector<edge>> g;

bool ford() {
    vector<ll> dist(g.size(), inf);
    vector<edge *> p(g.size(), nullptr);
    dist[0] = 0;
    for (int i = 0; i < g.size(); i++) {
        for (int j = 0; j < g.size(); j++) {
            for (edge &e : g[j]) {
                if (dist[j] < inf && e.f != e.a) {
                    if (dist[e.e] == inf || dist[e.e] > dist[j] + e.c) {
                        dist[e.e] = dist[j] + e.c;
                        p[e.e] = &e;
                    }
                }
            }
        }
    }
    if (dist[g.size() - 1] == inf) {
        return false;
    }
    vector<edge *> way;
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
        way[i]->f += mx;
        ans += way[i]->c * mx;
        g[way[i]->e][way[i]->rev].f -= mx;
    }
    return true;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    g.resize(8);
    int a;
    cin >> a;
    g[0].push_back({0, 1, 0, a, 0, (ll) g[1].size()});
    g[1].push_back({1, 0, 0, 0, 0, (ll) g[0].size() - 1});
    cin >> a;
    g[0].push_back({0, 2, 0, a, 0, (ll) g[2].size()});
    g[1].push_back({2, 0, 0, 0, 0, (ll) g[0].size() - 1});
    cin >> a;
    g[0].push_back({0, 3, 0, a, 0, (ll) g[3].size()});
    g[1].push_back({3, 0, 0, 0, 0, (ll) g[0].size() - 1});
    cin >> a;
    g[4].push_back({4, 7, 0, a, 0, (ll) g[7].size()});
    g[7].push_back({7, 4, 0, 0, 0, (ll) g[4].size() - 1});
    cin >> a;
    g[5].push_back({5, 7, 0, a, 0, (ll) g[7].size()});
    g[7].push_back({7, 5, 0, 0, 0, (ll) g[5].size() - 1});
    cin >> a;
    g[6].push_back({6, 7, 0, a, 0, (ll) g[7].size()});
    g[7].push_back({7, 6, 0, 0, 0, (ll) g[6].size() - 1});
    for (int i = 1; i <= 3; i++) {
        for (int j = 4; j <= 6; j++) {
            if ((i + 1) % 3 == j % 3) {
                g[i].push_back({i, j, 0, inf, 1, (ll) g[j].size()});
                g[j].push_back({j, i, 0, 0, -1, (ll) g[i].size() - 1});
                continue;
            }
            g[i].push_back({i, j, 0, inf, 0, (ll) g[j].size()});
            g[j].push_back({j, i, 0, 0, 0, (ll) g[i].size() - 1});
        }
    }
    while (ford());
    cout << ans;
}