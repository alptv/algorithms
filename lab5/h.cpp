#include <iostream>
#include <vector>

using namespace std;

struct node {
    int y;
    int allSymbol;
    char symbol;
    int size;
    int count;
    node * left, *right;

    node(char c, int a) {
        size = a;
        count = a;
        symbol = c;
        allSymbol = 1 << (int) (c - 'a');
        y = rand();
        left = right = nullptr;
    }
};

node *root = nullptr;



int trueSize(node* v) {
    if (!v) return 0;
    else return v->size;
}

void upd(node *v) {
    v -> size = trueSize(v->left) + trueSize(v->right) + v->count;
    v ->allSymbol = 1 << int(v->symbol - 'a');
    if (v->left) v->allSymbol |= v->left->allSymbol;
    if (v->right) v->allSymbol |= v->right->allSymbol;
}


node * merge(node * v1, node* v2) {
    if (!v1) return v2;
    if (!v2) return v1;

    if (v1->y > v2 -> y) {
        v1 -> right = merge(v1 -> right, v2);
        upd(v1);
        return v1;
    } else {
        v2 -> left = merge(v1, v2 ->left);
        upd(v2);
        return v2;
    }
}


pair <node*, node*> split(node* v, int key) {
    if (!v) return make_pair(nullptr, nullptr);

    if (trueSize(v->left) + v->count < key) {
        pair<node *, node *> cur = split(v->right, key - trueSize(v->left) - v->count);
        v->right = cur.first;
        upd(v);
        return make_pair(v, cur.second);
    }
    if (trueSize(v->left) + 1 > key) {
        pair<node *, node *> cur = split(v->left, key);
        v->left = cur.second;
        upd(v);
        return make_pair(cur.first, v);
    }
    key -= trueSize(v->left);
    node *right = v->right;
    node *left = v->left;

    node *t1 = new node(v->symbol, key - 1);
    node* t2 = new node (v ->symbol, v->count - key + 1);

    if (key - 1 != 0) left = merge(v ->left, t1);
    if (v -> count - key + 1 != 0) right = merge(t2, v->right);

    return make_pair(left,right);

}


void ins(int ind, int count, char c) {
    node* ins = new node(c, count);
    pair <node*, node*> cur = split(root, ind);
    root = merge(merge(cur.first, ins), cur.second);
}

void del(int index, int numb) {
    pair <node* ,node *> cur1 = split(root,index);
    pair <node*, node*> cur2 = split(cur1.second, numb + 1);
    root = merge(cur1.first, cur2.second);
}

void zapr(int l, int r) {
    pair <node* ,node *> cur1 = split(root,l);
    pair <node*, node*> cur2 = split(cur1.second, r - l + 2);
    int ans = 0;
    int check = cur2.first ->allSymbol;
    while (check != 0) {
        if ((check & 1) == 1) ans++;
        check >>= 1;
    }
    cout << ans << endl;
    root = merge(cur1.first, merge(cur2.first,cur2.second));
}

void print (node*v) {
    if (!v) return;
    print(v->left);
    for (int i =0; i < v->count; i++) {
        cout << v->symbol;
    }
    print(v->right);
}

int main() {
    int n;
    cin >> n;
    char c;
    int l,r;
    char check;
    int ind, count;
    for (int i = 0; i < n; ++i) {
        cin >> c;
        if (c == '+') {
            scanf("%d%d",&ind,&count);
            cin >> check;
            ins(ind, count, check);
        }
        if ( c == '-') {
            cin >> l >> r;
            del(l,r );
        }
        if ( c== '?') {
            scanf("%d%d", &l,&r);
            zapr(l , r);
        }

    }
}
