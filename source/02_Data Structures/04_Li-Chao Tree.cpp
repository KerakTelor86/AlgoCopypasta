// max li-chao tree
// works for the range [0, MAX - 1]
// if min li-chao tree:
// replace every call to max() with min() and every > with <
// also replace -INF with INF

struct Func {
  ll m, c;
  ll operator()(ll x) {
    return x * m + c;
  }
};

const int MAX = 1e9 + 1;
const ll INF = 1e18;
const Func NIL = {0, -INF};

struct Node {
  Func f;
  Node* lc;
  Node* rc;

  Node() : f(NIL), lc(nullptr), rc(nullptr) {}
  Node(const Node& n) : f(n.f), lc(nullptr), rc(nullptr) {}
};

Node* root = new Node;

void insert(Func f, Node* cur = root, int l = 0, int r = MAX - 1) {
  int m = l + (r - l) / 2;
  bool left = f(l) > cur->f(l);
  bool mid = f(m) > cur->f(m);
  if(mid)
    swap(f, cur->f);
  if(l != r) {
    if(left != mid) {
      if(!cur->lc)
        cur->lc = new Node(*cur);
      insert(f, cur->lc, l, m);
    } else {
      if(!cur->rc)
        cur->rc = new Node(*cur);
      insert(f, cur->rc, m + 1, r);
    }
  }
}

ll query(ll x, Node* cur = root, int l = 0, int r = MAX - 1) {
  if(!cur)
    return -INF;
  if(l == r)
    return cur->f(x);
  int m = l + (r - l) / 2;
  if(x <= m)
    return max(cur->f(x), query(x, cur->lc, l, m));
  else
    return max(cur->f(x), query(x, cur->rc, m + 1, r));
}
