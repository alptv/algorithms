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

vector<int> add(vector<int> &a, vector<int> &b, int sz) {
    vector<int> c(sz, 0);
    for (int i = 0; i < sz; i++) {
        c[i] = a[i] + b[i];
    }
    return c;
}
void sub(vector<int> &a, vector<int> &b, int sz) {
    vector<int> c(sz, 0);
    for (int i = 0; i < sz; i++) {
        if (i >= a.size()) {
            a.push_back(-b[i]);
        } else {
            a[i] -= b[i];
        }
    }
}

vector<int> mul(vector<int> &a, vector<int> &b, int sz) {
    if (sz <= 128) {
        vector<int> c(2 * sz, 0);
        for (int i = 0; i < sz; i++) {
            for (int j = 0; j < sz; j++) {
                c[i + j] += a[i] * b[j];
            }
        }
        return c;
    }
    int n = sz / 2;
    vector<int> a0(a.begin(), a.begin() + n);
    vector<int> a1(a.begin() + n, a.end());
    vector<int> b0(b.begin(), b.begin() + n);
    vector<int> b1(b.begin() + n, b.end());

    vector<int> a0b0 = mul(a0, b0, n);
    vector<int> a1b1 = mul(a1, b1, n);

    vector<int> sa0a1 = add(a0, a1, n);
    vector<int> sb0b1 = add(b0, b1, n);
    vector<int> sum = mul(sa0a1, sb0b1, n);
    sub(sum, a0b0,sz);
    sub(sum, a1b1, sz);
    vector<int> s2(sz + n, 0);
    for (int i = n; i < sz + n; i++) {
        s2[i] = sum[i - n];
    }
    vector<int> s3(2 *sz , 0);
    for (int i = sz; i < 2 * sz; i++) {
        s3[i] = a1b1[i - sz];
    }
    for (int i = 0; i < sz; i++) s3[i] += a0b0[i];
    for (int i = 0; i < sz + n; i++) s3[i] += s2[i];
    return s3;
}


int main() {
    freopen("duel.out", "w", stdout);
    freopen("duel.in", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    cin >> s;
    vector<int> a;
    a.reserve(s.size());
    for (int i = 0; i < s.size(); i++) a.push_back((int)s[i] - '0');
    int k = 1;
    while (k < a.size()) k *= 2;
    while (a.size() != k) a.push_back(0);
    auto c = mul(a, a, k);
    ll ans = 0;
    for (int i = 0; i < c.size(); i += 2) {
        if (a[i / 2] == 1)
        ans += (c[i] - 1) / 2;
    }
    cout << ans ;


}