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

int n;



int main() {
    cin >> n;
    int count = (n * (n - 1)) / 2 + n + 2;
    vector<vector<edge>> g(count);
    for (int i = 1; i <= (n * (n - 1)  / 2); i++) {
        g[0].push_back(edge(0, i, 3, 0,-1,1));
    }
    vector<vector<char>> field(n,vector(n,(char)0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          cin >> field[i][j];
        }
    }
    vector<int> need(n);
    for (int i = 0; i < n; i++) cin >> need[i];
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            char c = field[i][j];
            if (c == 'W') {
                need[i] -= 3;
            }
            if (c == 'w') {
                need[i] -= 2;
                need[j]  -= 1;
            }
            if (c == 'l') {
                need[i] -= 1;
                need[j] -= 2;
            }
            if (c == 'L') {
                need[j]  -= 3;
            }
            if (c == '.') {
                int ind = 0;
                for (int k = 0; k < min(i,j); k++) {
                    ind += n - k - 1;
                }
                ind += max(i, j) - min(i, j);
                int added = 1 + n * (n - 1) / 2;
                g[ind].push_back(edge(ind, i + added, 3, 0, -1, 1));
                g[ind].push_back(edge(ind, j + added, 3, 0, -1, 1));
            }
        }
    }
    for (int i = 0; i < n; i++) {
        g[i + (n *(n - 1)/ 2 + 1)].push_back(edge(i + (n *(n - 1)/ 2 + 1), count - 1, need[i], 0, -1, 1));
    }
    vector<vector<char>> a(field);
    flow f = flow(g, 0, count - 1);
    auto ans = f.getMaxFlow();
    int sum = 0;
    for (int i = 0; i < n; i++) sum += need[i];
    if (sum != ans.first) {
        cout << sum << ' ';
        cout << ans.first;
        return  -1;
    }
    map<pair<int,int>,int> mp;
    for (int i = 0; i < ans.second.size(); i++) {
        edge e = ans.second[i];
        mp[{e.from, e.to}] = e.f;
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (field[i][j] != '.') {
                continue;
            }
            int ind = 0;
            for (int k = 0; k < min(i,j); k++) {
                ind += n - k - 1;
            }
            ind += max(i, j) - min(i, j);
            int added = 1 + n * (n - 1) / 2;
            int first = mp[{ind, i + added}];
            if (first == 0) {
                a[i][j] = 'L';
                a[j][i] = 'W';
            }
            if (first == 1) {
                a[i][j] = 'l';
                a[j][i] = 'w';
            }
            if (first == 2) {
                a[i][j] = 'w';
                a[j][i] = 'l';
            }
            if (first == 3) {
                a[i][j] = 'W';
                a[j][i] = 'L';
            }
        }
    }
    for (int i =0; i < n; i++) {
        for (int j = 0;j < n; j++) {
            cout << a[i][j];
        }
        cout << '\n';
    }

}