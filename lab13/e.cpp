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


ll eu(ll x) {
    ll ans = x;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            while (x % i == 0) {
                x/= i;
            }
            ans -= ans / i;
        }
    }
    return x > 1 ? ans - ans / x : ans;
}

ll power(ll x, ll n, ll m) {
    ll ans = 1;
    while (n != 0) {
        if (n % 2== 1) {
            ans *= x;
            ans %= m;
            n--;
        } else {
            x *= x;
            x %=m;
            n/= 2;
        }
    }
    return ans;
}

ll rev(ll x ,ll f, ll m) {
    return power(x, f - 1, m);
}


int main() {
    ll n,e,c;
    cin >> n >> e >> c;
    ll f = eu(n);
    ll ff = eu(f);
    ll d = rev(e, ff, f);
    cout << power(c, d, n);
}