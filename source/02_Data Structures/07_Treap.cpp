// Complexity: O(log N) for split and merge
//
// empty treap: Treap* tr = nullptr;
// insert v at x: [l, r] = split(tr, x), m = Treap(v), merge lmr
// delete at x: [l, r] = split(tr, x), [m, r] = split(r, 1), merge lr
// lazy prop: propagate every time a node is accessed

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

using Key = int;

struct Treap {
  Key val;
  Treap* left;
  Treap* right;
  int prio, sz;
  Treap() {}
  Treap(int _val);
};

int size(Treap* tr) {
  return tr ? tr->sz : 0;
}

void update(Treap* tr) {
  tr->sz = 1 + size(tr->left) + size(tr->right);
}

Treap::Treap(Key _val) :
  val(_val), left(nullptr), right(nullptr), prio(rng()) {
  update(this);
}

pair<Treap*, Treap*> split(Treap* tr, int sz) {
  if(!tr) return {nullptr, nullptr};
  int left_sz = size(tr->left);
  if(sz <= left_sz) {
    auto [left, mid] = split(tr->left, sz);
    tr->left = mid;
    update(tr);
    return {left, tr};
  } else {
    auto [mid, right] = split(tr->right, sz - left_sz - 1);
    tr->right = mid;
    update(tr);
    return {tr, right};
  }
}

Treap* merge(Treap* l, Treap* r) {
  if(!l)
    return r;
  if(!r)
    return l;
  if(l->prio < r->prio) {
    l->right = merge(l->right, r);
    update(l);
    return l;
  } else {
    r->left = merge(l, r->left);
    update(r);
    return r;
  }
}
