#include "iostream"

using namespace std;

int t[128][128][128];

int prSum(int x, int y, int z) {
    int ans = 0;
    int i = x;
    int j = y;
    int k = z;
    while (i >=0) {

        while (j >= 0) {

            while (k >= 0) {

                ans += t[i][j][k];

                k = (k&(k+1)) - 1;
            }
            k = z;
            j = (j & (j+1)) -1;
        }
        j = y;
        i = (i & (i + 1)) - 1;
    }
    return ans;
}

void set(int x, int y, int z, int val, int n) {
    int i = x;
    int j = y;
    int k = z;
    while (i < n) {
        while (j < n) {
            while (k < n) {
                t[i][j][k] += val;
                k = k | (k+1);
            }
            k = z;
            j = j | (j+1);
        }
        j = y;
        i = i | (i + 1);
    }
}



int getAns(int x1,int x2, int y1,int y2, int z1, int z2) {
    int ans = prSum(x2 ,y2 ,z2) -prSum(x1 - 1,y2,z2) -prSum(x2,y1 - 1,z2) -prSum(x2,y2,z1 - 1)
    +prSum(x1 - 1,y1 - 1,z2) +prSum(x1 - 1,y2,z1 - 1) +prSum(x2,y1 - 1,z1 - 1) -prSum(x1 - 1,y1 - 1,z1 - 1);
    return ans;
}


int main() {

    int n;
    scanf("%d", &n);
    int check;
    while (true) {
        cin >> check;
        if (check == 3) {
            break;
        }
        if (check == 2) {
            int x1,x2,y1,y2,z1,z2;
            scanf("%d%d%d%d%d%d", &x1,&y1,&z1, &x2,&y2,&z2);
            printf("%d", getAns(x1,x2,y1,y2,z1,z2));
            printf("%s", "\n");
        }
        if (check == 1) {
            int x,y,z,k;
            scanf("%d%d%d%d", &x,&y,&z,&k);
            set(x,y,z,k,n);
    }
}