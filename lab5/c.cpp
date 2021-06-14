#include <iostream>
#include <string>
#include <random>
#include <time.h>
#include <algorithm>

using namespace std;
struct node {
    node *left, *right, *parent;
    int x,y,ind;

    node(int k) {
        x = k;
        y = rand();
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
    node(){
        left = right =parent= nullptr;
    }
    node (int k, int p) {
        x = k;
        y = p;
        left = right = parent = nullptr;
    }
    node (int k, int p,int ind_) {
        x = k;
        y = p;
        ind = ind_;
        left = right = parent=nullptr;
    }
};

node* last = nullptr;
node* root = nullptr;

void insert(int a, int b, int ind) {
    node * curr = new node(a,b,ind);
    if (!last) {
        last = curr;
        root = curr;
        return;
    }
    if (curr->y > last->y) {

        curr->parent = last;
        last->right = curr;
        last = curr;
        return;
    }
    while (last && curr->y < last->y) {
        last = last->parent;
    }
    if (!last) {
        root ->parent = curr;
        curr->left = root;
        last = curr;
        root = curr;
    } else {
        curr ->left = last->right;
        last->right->parent = curr;
        last->right = curr;
        curr ->parent = last;
        last = curr;
    }
}



int ans[300006][3];

void print(node* v) {
    if (!v) return;
    print(v->left);
    if (!v->parent) ans[v->ind][0] = 0;
    else ans[v->ind][0] = v -> parent -> ind;
    if (!v->left)  ans[v->ind][1] = 0;
    else  ans[v->ind][1] =  v ->left  -> ind;
    if (!v->right)  ans[v->ind][2] = 0;
    else  ans[v->ind][2] = v -> right-> ind;
    print(v->right);
}



int main() {
    int n, a , b;
    string s;
    cin >> n;
    pair<int, pair<int,int>> c[300006];
    for (int i = 0; i < n; i++){
        cin >>  a >> b;
        c[i] = make_pair(a,(make_pair(b,i+1)));
    }
    sort(c,c+n);
    for (int i = 0; i < n; i++){
        insert(c[i].first,c[i].second.first, c[i].second.second);
    }
    cout << "YES" << endl;
    print(root);
    for (int i = 0; i < n; i++){
        cout << ans[i+1][0] << " " << ans[i+1][1] << " " <<  ans[i+1][2] << endl;
    }



}