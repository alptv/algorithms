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

struct t {
    ll s, a, b;
};

 t gcd(ll a, ll b) {
    if (b == 0) return {a,1, 0};
    t x  = gcd(b, a % b);
     return {x.s,x.b,x.a- x.b*(a/b)};
}


int main() {
  ll a, b,n,m;
  cin >> a >> b >> n >> m;
  t x;
  x = gcd(n, m);
  ll ans  = n * x.a * (b - a);
  ans += a;
  while (ans < 0) ans += n * m;
  ans %= n * m;
  cout << ans;
}