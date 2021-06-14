#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <queue>

using namespace std;


const int MAXN = 10005;

bool used[MAXN];
double minEdge[MAXN];

vector <pair <int, int>> dots;

int main() {
    int n;
    cin >> n;
    int x, y;
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        dots.emplace_back(x, y);
    }
    double cost = 0;
    used[0] = true;
    x = dots[0].first;
    y = dots[0].second;
    for (int i = 1; i < n; i++) {
        minEdge[i] = sqrt((x - dots[i].first)*(x - dots[i].first) + (y - dots[i].second)*(y - dots[i].second));
    }
    for (int i = 1; i < n; i++) {
        double minimal = 3*10000;
        int ind = -1;
        for (int j = 0; j < n; j++) {
            if (!used[j]) {
                if (minEdge[j] < minimal) {
                    minimal = min(minimal, minEdge[j]);
                    ind = j;
                }
            }
        }
        cost += minimal;
        used[ind] = true;
        x = dots[ind].first;
        y = dots[ind].second;
        for (int j = 0; j < n; j++) {
            if (!used[j]) {
                minEdge[j] = min(minEdge[j], sqrt((x - dots[j].first)*(x - dots[j].first) + (y - dots[j].second)*(y - dots[j].second)));
            }
        }
    }
    cout << cost;
}