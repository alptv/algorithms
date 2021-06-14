#include <iostream>
using namespace std;

long long a[(int)1e7 + 3];
int c[(int) 2e7 + 10];

long long const m1 = 65535;
long long const m2 = 1073741823;

long long mod16(long long a) {
    return a & m1;
}
long long min(long long a ,long long c) {
    return a > c ? c : a;
}
long long max(long long a ,long long c) {
    return a > c ? a : c;
}

long long mod30(long long a) {
    return a & m2;
}

int main() {
    int x,y,n,a0;
    int m,z,t;
    int c0;
    cin >> n >> x >> y >> a0;
    cin >> m >> z >> t >> c0;
    x = (int)mod16(x);
    y = (int)mod16(y);
    t = (int)mod30(t);
    z = (int)mod30(z);
    a[0] = a0;
    c[0]= c0;
    long long ans = 0;
    for (long long i = 1; i < n; i++) {
        a[i] = mod16(mod16((long long)x * a[i - 1]) + y);
    }
    for (long long i = 1; i < 2*m + 2; i++) {
        c[i] = (int) mod30(mod30((long long) z * c[i - 1]) + t);

    }
    for (long long i = 0; i < 2*m + 2; i++) {
        c[i] = c[i] % n;
    }
    for (long long i = 1; i < n; i++) {
        a[i] = a[i] + a[i-1];
    }
    for (long long i = 0; i < m; i++) {
        long long ma = max(c[2*i],c[2*i+1]);
        long long mi = min(c[2*i],c[2*i+1]);
        if (mi == 0) {
            ans += a[ma];
            continue;
        }
        ans+= a[ma] - a[mi - 1];
    }
    cout << ans;
    return 0;


}