// Represents a forest of unrooted trees. You can add and remove edges
// (as long as the result is still a forest), and check whether two
// nodes are in the same tree.
// Complexity: log(n)

struct Node { // Splay tree. Root's pp contains tree's parent.
  Node* p = 0, *pp = 0, *c[2];
  int sz = 0;
  //
  Node() {
    c[0] = c[1] = 0;
    fix();
  }
  void fix() {
    sz = 1;
    if(c[0]) c[0]->p = this, sz += c[0]->sz;
    if(c[1]) c[1]->p = this, sz += c[1]->sz;
    // (+ update sum of subtree elements etc. if wanted)
  }
  int up() {
    return p ? p->c[1] == this : -1;
  }
  void rot(int i, int b) {
    int h = i ^ b;
    Node* x = c[i], *y = (b == 2 ? x : x->c[h]), *z = (b ? y : x);
    if(y->p = p) p->c[up()] = y;
    c[i] = z->c[i ^ 1];
    if(b < 2) x->c[h] = y->c[h ^ 1], z->c[h ^ 1] = b ? x : this;
    y->c[i ^ 1] = b ? this : x;
    fix();
    x->fix();
    y->fix();
    if(p) p->fix();
    swap(pp, y->pp);
  }
  // Splay this up to the root. Always finishes without flip set.
  void splay() {
    while(p) {
      int c1 = up(), c2 = p->up();
      if(c2 == -1) p->rot(c1, 2);
      else p->p->rot(c2, c1 != c2);
    }
  }
};
struct LinkCut {
  vector<Node> node;

  LinkCut(int N) : node(N + 1) {}
  void link(int u, int v) { // add an edge u --> v
    assert(!connected(u, v));
    access(&node[u]);
    access(&node[v]);
    node[u].c[0] = &node[v];
    node[v].p = &node[u];
    node[u].fix();
  }
  void cut(int u, int v) { // remove an edge u --> v
    assert(connected(u, v));
    Node* x = &node[v], *top = &node[u];
    access(top);
    top->c[0] = top->c[0]->p = 0;
    top->fix();
  }
  bool connected(int u, int v) { // are u, v in the same tree?
    return root(u) == root(v);
  }
  int root(int u) { // find the root id of node u
    Node* x = &node[u];
    access(x);
    for(; x->c[0]; x = x->c[0]);
    x->splay();
    return (int)((vector<Node>::iterator)x - node.begin());
  }
  // Move u to root aux tree. Return the root of the root aux tree.
  Node* access(Node* u) {
    u->splay();
    Node* last = u;
    if(Node*& x = u->c[1]) {
      x->pp = u;
      x->p = 0;
      x = 0;
      u->fix();
    }
    for(Node * pp; (pp = u->pp) && (last = pp);) {
      pp->splay();
      if(pp->c[1]) pp->c[1]->p = 0, pp->c[1]->pp = pp;
      pp->c[1] = u;
      u->p = pp;
      u->pp = 0;
      pp->fix();
      u->splay();
    }
    return last;
  }
  int depth(int u) {
    access(&node[u]);
    return node[u].sz - 1;
  }
  Node* lca(int u, int v) {
    access(&node[u]);
    return access(&node[v]);
  }
};

