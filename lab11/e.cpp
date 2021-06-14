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
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int INF = 10000000;

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
                g[e.from].push_back(edge(e.from, e.to, e.c, e.f, -1, e.i));
                g[e.to].push_back(edge(e.to, e.from, 0, -e.f, -1, 0));
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

const int DAYS = 105;

int main() {
    int n, m, k;
    int s,t;
    cin >> n >> m >> k;
    cin >> s >> t;
    set<pair<int,int>> edg;
    for (int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        edg.insert({x,y});
        edg.insert({y,x});
    }
    map<pair<int,int>,pair<int,int>> prom;
    vector<vector<edge>> g(1 + n * DAYS);
    int next = 1 + n * DAYS;
    g[0].push_back(edge(0, s, k, 0, -1, 1));
    for (int i = 0; i < DAYS -1 ; i++) {
        for (int x = 1; x <= n; x++) {
            for (int y = x; y <= n; y++){
                if (x == y) {
                    g[i * n + x].push_back(edge(i * n + x, (i + 1)* n + y, INF,0,-1,1));
                } else if (edg.count({x, y})){
                    prom[{i * n + x,i * n + y}] = {next, next + 1};
                    prom[{i * n + y,i * n + x}] = {next, next + 1};
                    g.emplace_back();
                    g.emplace_back();
                    g[next + 1].push_back(edge(next + 1, (i + 1)* n + y, 1,0,-1,1));
                    g[next + 1].push_back(edge(next + 1, (i + 1)* n + x, 1,0,-1,1));
                    g[i * n + x].push_back(edge(i * n + x, next, 1,0,-1,1));
                    g[i * n + y].push_back(edge(i * n + y, next, 1,0,-1,1));
                    g[next].push_back(edge(next, next + 1,  1, 0, -1,1));
                    next+=2;
                }
            }
        }
    }
    for (int i = 1; i < DAYS; i++) {
        flow f = flow(g, 0, i * n + t);
        auto ans = f.getMaxFlow();
        if (ans.first == k) {
            cout << i << "\n";
            vector<set<int>> day(n + 1);
            vector<set<int>> next(n + 1);
            for (int j = 1; j <=k; j++) day[s].insert(j);
            map<pair<int,int>,int> edges;
            for (edge e : ans.second) {
                edges[{e.from, e.to}] = e.f;
            }
            for (int j = 0; j < i; j++) {
                int c = 0;
                for (int x = 1; x <= n; x++) {
                    for (int y = 1; y <= n; y++) {
                        if (edg.count({x, y}) && x != y) {
                            if (edges[{j*n +x , prom[{j * n + x, j * n + y}].first}] > 0 &&
                                    edges[{prom[{j * n + x, j * n + y}].second , (j + 1)* n + y}] > 0) {
                                c += 1;
                            }
                        }
                    }
                }
                cout << c << "  ";
                for (int x = 1; x <= n; x++) {
                    for (int y = 1; y <= n; y++) {
                        if (x == y) {
                            int count = edges[{j * n + x, (j + 1) * n + x}];
                            while (count--) {
                                int go = *day[x].begin();
                                day[x].erase(go);
                                next[x].insert(go);
                            }
                            continue;
                        }
                        if (edg.count({x, y})) {
                            int a = edges[{j * n + x, prom[{j * n + x, j  * n + y}].first}];
                            int b = edges[{prom[{j * n + x, j  * n + y}].second, (j + 1) * n + y}];
                            int d = edges[{prom[{j * n + x, j  * n + y}].second, (j + 1) * n + x}];
                            if (a != 0) {
                                if (b == 1) {
                                    int go = *(day[x].begin());
                                    cout << go << ' ' << y << ' ';
                                    day[x].erase(go);
                                    next[y].insert(go);
                                } else if (d == 1){
                                    int go = *(day[x].begin());
                                    day[x].erase(go);
                                    next[x].insert(go);
                                }
                            }
                        }
                    }
                }
                day = next;
                next.assign(n + 1, {});
                cout << '\n';
            }
            return 0;
        }
    }
}