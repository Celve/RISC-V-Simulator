#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>

#define MAXN 1000005

#define ls x << 1
#define rs x << 1 | 1

using namespace std;

class SegmentTree {
  class Node {
    int l, r, v;
    Node() { v = 0; };
  } t[MAXN << 2];

  void Build(int l, int r, int x = 1) {
    t[x].l = l;
    t[x].r = r;
    if (l == r) {
      return;
    }
    int mid = (t[x].l + t[x].r) >> 1;
    build(l, mid, ls);
    build(mid + 1, r, rs);
  }

  void Modify(int p, int x = 1) {
    if (t[x].l == t[x].r) {
      return;
    }
    int mid = (t[x].l + t[x].r) >> 1;
    Modify(p, x << 1);
  }
};

int main() {}