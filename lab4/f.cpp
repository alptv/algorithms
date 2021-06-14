#include <iostream>

using namespace std;

int sparse[100005][20];
int a[100005];
int pod[100005];

int modInt(int a, int mod) {
    if (a < mod) return a;
    return a % mod;
}


int min (int a, int b) {
    return a > b ? b : a;
}
int max (int a, int b) {
    return a > b ? a : b;
}

int bit(int x) {
    int t = 1;
    int ans = 0;
    while (x >= t) {
        t <<= 1;
        ans++;
    }
    ans--;
    return ans;
}

int get(int start, int end) {
    int x = pod[end -  start + 1];
    return min(sparse[start][x], sparse[end - (1 << x) + 1][x]);
}






int main() {
    int n,m,start, end, ans;
    scanf("%d%d%d", &n, &m, &a[0]);
    scanf("%d%d", &start, &end);

    for (int i = 1; i <=n; i++) {
        pod[i] = bit(i);
    }
    for (int i = 1; i < n; i++) {
        a[i] = modInt((23*a[i - 1] + 21563),16714589);
    }
    for (int j = 0;  (1 << j)  <= n; j++) {
        for (int i = 0; (i +(1 << j)) <= n; i++) {
            if (j == 0) {
                sparse[i][j] = a[i];
                continue;
            }
            sparse[i][j] = min(sparse[i][j - 1] , sparse[i + (1 << (j-1))][j - 1]);
        }
    }
    ans = get(min(start - 1,end - 1),max(start - 1,end - 1));
    for (int i = 1; i < m; i++) {
        start = modInt((17*start+751 + ans + 2 * i),n) + 1;
        end = modInt(13*end+593+ans + 5 *i, n) + 1;
        ans = get(min(start-1,end-1),max(start - 1,end-1));
    }
    cout << start << " " << end << " " << ans;


}