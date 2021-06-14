#include <iostream>
#include <string>
#include <random>
#include <time.h>

using namespace std;
struct node {
    node *left, *right;
    int y, size, number, index;
    bool hasZero;

    node(int k) {
        number = k;
        index  = -1;
        y = rand();
        size = 1;
        left = nullptr;
        right = nullptr;
        hasZero = true;
    }
    node () {
        hasZero = false;
        index = 1;
        number = 0;
        y = rand();
        size = 1;
        left = nullptr;
        right = nullptr;
    }
};

node* root = nullptr;


int trueVal(node *v) {
    if (!v) return 0;
    return v->size;
}

int ind(node *v) {
    if (!v) return -1;
    return  v->index;
}
bool zer(node* v) {
    if (!v) return false;
    return v->hasZero;
}


void upd(node *v) {
    v->size =  trueVal(v->right) + trueVal(v->left) + 1;
    v->hasZero = zer(v->right) || zer(v->left) || v->number != 0;
    if (ind(v->left) != -1) {
        v->index = v->left -> index;
        return;
    }
    if (v->number == 0) {
        v->index = trueVal(v->left) + 1;
        return;
    }

    if (ind(v->right) != -1) {
        v->index = v->right->index + trueVal(v->left) + 1;
        return;
    }
    v->index = -1;
}

pair<node*, node*> split(node *v, int key) {
    if (!v) {
        return make_pair(nullptr, nullptr);
    }
    if (trueVal(v->left) + 1  < key) {
        pair<node *, node *> cur = split(v->right, key - trueVal(v->left)- 1);
        v->right = cur.first;
        upd(v);
        return make_pair(v, cur.second);
    } else {
        pair<node *, node *> cur = split(v->left, key);
        v->left = cur.second;
        upd(v);
        return make_pair(cur.first, v);
    }
}


node* merge(node *a, node* b) {
    if (!a) return  b;
    if (!b) return a;
    if (b->y > a->y) {
        b->left = merge(a , b-> left);
        upd(b);
        return b;
    } else {
        a->right = merge(a->right, b);
        upd(a);
        return  a;
    }
}

void print(node *v, int &count, int m){
    if (!v)return;
    if (count == m) return;
    print(v->left, count, m);
    if (count == m) return;
    printf("%d", v->number);
    if (v->number != 0) {
        count++;
    }
    if (count == m) return;
    printf("%c", ' ');
    print(v->right, count, m);
    if (count == m) return;
}


void insert(int key, int numb) {
    node* add = new node(numb);
    node* ans;
    pair<node*,node*> cur = split(root, key);
    int c = 0;
    int k = 0;

    int pos = ind(cur.second);

    if (pos == 1) {

        root = merge(cur.first, merge(add, split(cur.second, 2).second));
        return;
    }
    pair <node*, node*> b;
    b = split(cur.second, pos);
    ans = merge(add, b.first);

    b = split(b.second, 2);
    ans = merge(cur.first, merge(ans, b.second));
    root = ans;
  
}

void ins(int key) {
    node* add = new node();
    node*ans;
    pair<node*,node*> cur = split(root, key);
    ans = merge(cur.first, add);
    ans = merge(ans, cur.second);
    root = ans;
}

int ans(node *v, int &an) {
    if (!v) return -1;
        if (zer(v->right)) {
        an+= trueVal(v->left) + 1;
        return ans(v->right, an);
}
    if (v->number != 0) return an + trueVal(v->left) + 1;
     if (zer(v->left)) return ans(v->left, an);

}




int main() {
    int n, m;
    cin >> n;
        cin >> m;
    for (int i = 0; i < 300000; i++) {
        ins(i + 1);
    }

    int x;
    for (int i = 1; i <= n; i++) {
      cin >> x;
      insert(x,i);
    }
    int count = 0;
    int an = 0;
    cout << ans(root, an);
    cout << endl;
    print(root, count, n);
}