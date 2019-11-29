#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100005;

namespace segment_tree
{
int N = MAX_N;
int leaf[MAX_N];
int tree[MAX_N];
int lazUpd[MAX_N];
int a[MAX_N];

void build_tree(int node, int l, int r)
{
    if (l == r)
    {
        leaf[l] = node;
        tree[node] = a[l];
        return;
    }
    build_tree(node * 2, l, (l + r) / 2);
    build_tree(node * 2 + 1, (l + r) / 2 + 1, r);
}

void propagate(int node, int l, int r)
{
    tree[node] += lazUpd[node];
    if (l < r)
    {
        lazUpd[node * 2] += lazUpd[node];
        lazUpd[node * 2 + 1] += lazUpd[node];
    }
    lazUpd[node] = 0;
}

void update(int u, int v, int value, int node, int l, int r)
{
    if (u > r || v < l)
        return;
    if (u <= l && r <= v)
    {
        lazUpd[node] += value;
    }
    else
    {
        update(u, v, value, node * 2, l, (l + r) / 2);
        update(u, v, value, node * 2, (l + r) / 2 + 1, r);
    }
}

int get(int u, int v, int node, int l, int r)
{
    if (u > r || v < l)
        return 0;
    if (u <= l && r <= v)
    {
        propagate(node, l, r);
        return tree[node];
    }
    else
    {
        return get(u, v, node * 2, l, (l + r) / 2) +
               get(u, v, node * 2, (l + r) / 2 + 1, r);
    }
}

} // namespace segment_tree

int main()
{
    segment_tree::N = 10;
    for (int i = 1; i <= segment_tree::N; ++i) {
        segment_tree::a[i] = 1;
    }
    
    return 0;
}
