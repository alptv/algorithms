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
int MAXV;

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



struct event {
    int m;
    int x;
    int y;

    bool can(event b) {
        double dist = sqrt((x - b.x) * (x - b.x) + (y - b.y)*(y - b.y));
        double time = (dist * 1000)/((double)(MAXV * 50) / 3);
        return  (m < b.m) && ((b.m - m) >= time);

    }

};



int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("ufo.in", "r", stdin);
    freopen("ufo.out", "w", stdout);
    int n;
    cin >> n >> MAXV;
    g.assign(n, {});
    p.assign(n, -1);
    used.assign(n, -1);
    vector<event> events(n);
    for (event &x : events) {
        string s; cin >> s;
        int t = ((int)(s[0] - '0') * 10 + (int)(s[1] - '0')) * 60 + (int)(s[3] - '0') * 10 + (int)(s[4] - '0');
        x.m = t; cin >> x.x >> x.y;
    }

    for (int i = 0; i < events.size(); i++) {
        for (int j = 0; j < events.size(); j++) {
            if (events[i].can(events[j])) {
                g[i].pb(j);
            }
        }
    }
    for (int i = 0; i < n; i++){
        dfs(i);
        c++;
    }
    int ans = 0;
    for (int x : p) ans += (x >= 0) ? 1 : 0;
    cout << n - ans << '\n';
}