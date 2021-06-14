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

ll inf = (ll) 1e9;
ll ans = 0;

struct edge {
    ll s, e, f, a, c, rev;
};

vector<vector<edge>> g;

bool ford() {
    vector<ll> dist(g.size(), inf);
    vector<edge*> p(g.size(), nullptr);
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
    g.resize(n);
    for (int i = 0; i < m; i++) {
        int s, e, a,c;
        cin >> s >> e >>a >> c;
        s--; e--;
        ll r1 = g[s].size();
        ll r2 = g[e].size();
        g[s].push_back({s,e,0,a,c,r2});
        g[e].push_back({e,s,0,0,-c,r1});
    }
    while (ford());
    cout << ans;
}