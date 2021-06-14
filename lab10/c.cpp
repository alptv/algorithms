#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <fstream>


using namespace std;


vector<vector<int>> g;
vector<int> p;
vector<int> used;
vector<int> path;
vector<int> cost;


int c;


void fll(int n) {
    g.assign(n, {});
    p.assign(n, -1);
    used.assign(n, -1);
    c = 0;
    path.assign(n, -1);
    cost.assign(n, 0);
}

int dfs(int v) {
    used[v] = c;
    int max_cost = -1;
    int max_v = -1;
    for (int u : g[v]) {
       if (used[u] == c) continue;
       if (p[u] == -1 && max_cost < cost[u]) {
           max_cost = cost[u];
           max_v = u;
       } else if (used[p[u]] != c && p[u] != -1){
           int c = dfs(p[u]);
           if (max_cost < c) {
               max_cost = c;
               max_v = u;
           }
       }
    }
    path[v] = max_v;
    return max_cost;
}



int main() {
    int n, m, e;
   // fstream in("C:/C++/CodeForces/a.txt");
    cin >> n >> m >> e;
    fll(n + m);
    set<pair<int,int>> v_cost;
    for (int i = 0; i < n + m; i++) {
        int c;
        cin >> c;
        cost[i] = c;
        v_cost.insert({-c, i});
    }
    map<pair<int,int>,int> b;
    for (int i = 0; i < e; i++) {
        int x, y; cin >> x >> y; x--; y--; y += n;
        g[x].push_back(y);
        g[y].push_back(x);
        b[{min(x,y),max(x,y)}] = i;
    }
    while (v_cost.size()) {
        pair<int,int> v = *(v_cost.begin());
        v_cost.erase(v);
        if (dfs(v.second) != -1) {
            int x = v.second;
            while (true) {
                int y = path[x];
                int next = p[y];
                p[y] = x;
                p[x] = y;
                if (next == -1) {
                    v_cost.erase({-cost[y], y});
                    break;
                }
                x = next;
            }
        }
        c++;
    }
    set<int> a;
    int ans = 0;
    for (int i = 0; i < n + m; i++) {
        if (p[i] != -1) {
            a.insert(b[{min(i,p[i]), max(i, p[i])}]);
            ans += cost[i] + cost[p[i]];
        }
    }
    cout << ans / 2<< '\n';
    cout << a.size() << '\n';
    for (int x : a) cout << x + 1 << " ";
    return 0;
}