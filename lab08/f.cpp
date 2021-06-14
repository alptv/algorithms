#include <iostream>
#include <vector>
#include <set>


using namespace std;

const long long INF = (long long) 1e15;

vector <vector<pair<int, long long>>> g;

long long min(long long a, long long b, long long c) {
    if (a > b)
        swap(a, b);
    if (a > c)
        swap(a, c);
    return a;
}

int n, m;

vector<long long> distanse(int s) {
    vector <long long> d(n , INF);
    d[s] = 0;
    set <pair <long long, int >> heap;
    for (int i = 0; i < n; i++) {
        heap.insert({d[i], i});
    }
    for (int i = 0; i < n; i++) {
        int v = (*heap.begin()).second;
        heap.erase(heap.begin());
        for (auto edge : g[v]) {
            long long w = edge.second;
            int u  = edge.first;
            if (d[u] > d[v] + w) {
                heap.erase({d[u], u});
                d[u] = d[v] + w;
                heap.insert({d[u], u});
            }
        }
    }
    return d;
}


int main() {
    cin >> n >> m;
    g.assign(n, {});
    for (int i = 0; i < m; i++) {
        int x, y; long long w;
        cin >> x >> y >> w;
        x--; y--;
        g[x].push_back({y, w});
        g[y].push_back({x, w});
    }
    int a, b, c;
    cin >> a >> b >> c;
    a--; b--; c--;
    vector<long long> da = distanse(a);
    vector<long long> db = distanse(b);
    vector<long long> dc = distanse(c);

    bool ab = da[b] == INF;
    bool bc = db[c] == INF;
    bool ca = dc[a] == INF;

    if (ab || bc || ca) {
        cout << -1;
        return 0;
    }
    long long ans = min(da[b] + db[c], da[c] + dc[b], dc[a] + da[b]);
    cout << ans;

}