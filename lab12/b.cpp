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

const ll INF = (ll) 1e9;

vector<vector<ll>> matr;
int n, m;

vector<pair<ll,ll>> solve() {
    vector<ll> ind(m, -1);
    vector<ll> line(n, 0);
    vector<ll> col(m, 0);
    for (int i = 0; i < n; i++) {
        vector<ll> back(m, -1);
        vector<ll> mn(m, INF);
        vector<bool> used(m, false);
        ll ii = i, jj = -1, index;
        for (;ii != -1;) {
            index = -1;
            for (int j = 0; j < m; j++){
                if (!used[j] && matr[ii][j] - line[ii] - col[j] < mn[j]) {
                    mn[j] =  matr[ii][j] - line[ii] - col[j];
                    back[j] = jj;
                }
                if (!used[j] && index == -1) {
                    index = j;
                    continue;
                }
                if (!used[j] && mn[index] > mn[j]) index = j;
            }
            ll d = mn[index];
            for (int j = 0; j < m; j++){
                if (!used[j]) {
                    mn[j] -= d;
                    continue;
                }
                line[ind[j]] += d;
                col[j] -= d;
            }
            line[i] += d;
            used[index] = true;
            jj = index;
            ii = ind[jj];
        }
        while(back[jj] != -1) {
            ind[jj] = ind[back[jj]];
            jj = back[jj];
        }
        ind[jj] = i;
    }
    vector<pair<ll,ll>> ans;
    for (int i = 0; i < m; i++) {
        if (ind[i] != -1) {
            ans.emplace_back(ind[i],i);
        }
    }
    return ans;
}


int main() {
    cin >> n;
    m = n;
    matr.resize(n, vector<ll>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matr[i][j];
        }
    }
    auto x = solve();
    ll ans = 0;
    for (auto p : x) {
        ans += matr[p.first][p.second];
    }
    cout << ans << '\n';
    for (auto p : x) {
        cout << p.first + 1 << ' ' << p.second + 1 << '\n';
    }
}