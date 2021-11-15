class PersistentSegtree {
private:
  int n, ptr, sz;
  struct P {
    int val = 0, l, r;
  };
  vector<P> node;
  vector<int> root;

  int newNode() {
    node.emplace_back();
    return ptr++;
  }
  int copyNode(int idx) {
    node.push_back(node[idx]);
    return ptr++;
  }
  int build(int l, int r) {
    int idx = newNode();
    if(l == r)
      return idx;
    node[idx].l = build(l, (l + r) / 2);
    node[idx].r = build((l + r) / 2 + 1, r);
    return idx;
  }
  int update(int idx, int l, int r, int x, int val) {
    idx = copyNode(idx);
    if(l == r) {
      node[idx].val += val;
      return idx;
    }
    int mid = (l + r) / 2;
    if(x <= mid)
      node[idx].l = update(node[idx].l, l, mid, x, val);
    else
      node[idx].r = update(node[idx].r, mid + 1, r, x, val);
    node[idx].val = node[node[idx].l].val + node[node[idx].r].val;
    return idx;
  }
  int query(int idxl, int idxr, int l, int r, int x, int y) {
    if(y < l || r < x)
      return 0;
    if(x <= l && r <= y)
      return node[idxr].val - node[idxl].val;
    int mid = (l + r) / 2;
    return query(node[idxl].l, node[idxr].l, l, mid, x, y)
           + query(node[idxl].r, node[idxr].r, mid + 1, r, x, y);
  }

public:
  PersistentSegtree(int _n) : n(_n), ptr(0) {
    sz = 30 * n;
    node.reserve(sz);
    root.push_back(build(1, n));
  }
  void update(int x, int val) {
    root.push_back(update(root.back(), 1, n, x, val));
  }
  int query(int l, int r, int x, int y) {
    return query(root[l - 1], root[r], 1, n, x, y);
  }
};

