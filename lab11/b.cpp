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

using namespace std;
#define pb push_back
#define pf push_front
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct edge {
    int from, to, rev, i;
    int f,c;
    edge(int from, int to, int c, int f, int rev, int i) : from(from),to(to), c(c), f(f), rev(rev), i(i){}
};


struct flow {
    int s, t;
    vector<vector<edge>> g;
    ull n;
    int INF = 100000000;

    flow(vector<vector<edge>> &gr, int s, int t) : s(s) , t(t) {
        n = gr.size();
        g.resize(n);
        for (int j = 0; j < n; j++){
            for (int i = 0; i < gr[j].size(); i++) {
                edge e = gr[j][i];
                g[e.from].emplace_back(e.from, e.to, e.c, e.f, -1, e.i);
                g[e.to].emplace_back(e.to, e.from, 0, -e.f, -1, 0);
                g[e.from][g[e.from].size() - 1].rev = (int)g[e.to].size() - 1;
                g[e.to][g[e.to].size() - 1].rev = (int)g[e.from].size() - 1;
            }
        }
    }

    vector<edge> getEdges() {
        vector<edge> ans;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < g[i].size(); j++) {
                auto x  = g[i][j];
                if (g[i][j].i > 0) {
                    ans.push_back(g[i][j]);
                }
            }
        }
        return ans;
    }

    pair<int, vector<edge>> getMaxFlow() {
        vector<int> used(n, 0);
        int f = 0;
        while(true) {
            int delta = dfs(s, used, INF);
            if (delta <= 0) {
                break;
            }
            f += delta;
            used.assign(n, false);
        }
        vector<edge> ans = getEdges();
        return {f, ans};
    }


    int dfs(int v, vector<int> &used, int delta) {
        used[v] = 1;
        if (v == t) {
            return delta;
        }
        for (edge &e : g[v]) {
            if (e.c  - e.f > 0 && !used[e.to]) {
                int d = dfs(e.to, used, min(delta, e.c - e.f));
                if (d > 0) {
                    e.f += d;
                    g[e.to][e.rev].f -= d;
                    return d;
                }
            }
        }
        return 0;
    }

    pair<int, vector<edge>> minCut() {
        vector<edge> edges;
        int size = 0;
       getMaxFlow();
       vector<int> used;
       used.assign(n, 0);
       dfs(s, used);
       for (int v = 0; v < n; v++) {
           if (used[v]) {
               for (edge e : g[v]) {
                   if (e.i > 0 && !used[e.to]) {
                       size++;
                       edges.push_back(e);
                   }
               }
           }
       }
        return {size, edges};
    }


    void dfs(int v, vector<int> &used) {
        used[v] = 1;
        for (edge e : g[v]) {
            if (e.c - e.f > 0 && !used[e.to]) {
                dfs(e.to, used);
            }
        }
    }
};


int main() {
    int n;
    int m;
    cin >> n >> m;
    vector<vector<edge>> g;
    g.resize(n);
    set<pair<pair<int, int>, int>> edges;
    for (int i = 0; i < m; i++) {
        int x, y;
        int c;
        cin >> x >> y >> c;
        x--; y--;
        g[x].emplace_back(x, y, c, 0, -1, i + 1);
        g[y].emplace_back(y, x, c, 0, -1, i + 1);
    }
    auto ans = flow(g, 0, n - 1).minCut();
    cout << ans.first << ' ';
    int s = 0;
    for (int i = 0; i < ans.second.size(); i++) s += ans.second[i].c;
    cout << s << '\n';
    sort(ans.second.begin(), ans.second.end(), [](edge x, edge y) {
        return x.i <= y.i;
    });
    for (int i = 0; i < ans.second.size(); i++) {
        cout << ans.second[i].i << ' ';
    }
}