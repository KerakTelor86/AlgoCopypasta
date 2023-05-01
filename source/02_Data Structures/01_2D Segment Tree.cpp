struct Segtree2D {
  struct Segtree {
    struct node {
      int l, r, val;
      node* lc, *rc;
      node(int _l, int _r, int _val = INF) : l(_l), r(_r), val(_val),
      lc(NULL), rc(NULL) {}
    };
    typedef node* pnode;

    pnode root;

    Segtree(int l, int r) {
      root = new node(l, r);
    }

    void update(pnode& nw, int x, int val) {
      int l = nw->l, r = nw->r, mid = (l + r) / 2;
      if(l == r)
        nw->val = val;
      else {
        assert(l <= x && x <= r);
        pnode& child = x <= mid ? nw->lc : nw->rc;
        if(!child)
          child = new node(x, x, val);
        else if(child->l <= x && x <= child->r)
          update(child, x, val);
        else {
          do {
            if(x <= mid)
              r = mid;
            else
              l = mid + 1;
            mid = (l + r) / 2;
          } while((x <= mid) == (child->l <= mid));
          pnode nxt = new node(l, r);
          if(child->l <= mid)
            nxt->lc = child;
          else
            nxt->rc = child;
          child = nxt;
          update(nxt, x, val);
        }
        nw->val = min(nw->lc ? nw->lc->val : INF,
                      nw->rc ? nw->rc->val : INF);
      }
    }

    int query(pnode& nw, int x1, int x2) {
      if(!nw)
        return INF;
      int& l = nw->l, &r = nw->r;
      if(r < x1 || x2 < l)
        return INF;
      if(x1 <= l && r <= x2)
        return nw->val;
      int ret = min(query(nw->lc, x1, x2),
                    query(nw->rc, x1, x2));
      return ret;
    }

    void update(int x, int val) {
      assert(root->l <= x && x <= root->r);
      update(root, x, val);
    }

    int query(int l, int r) {
      return query(root, l, r);
    }
  };

  struct node {
    int l, r;
    Segtree y;
    node* lc, *rc;
    node(int _l, int _r) : l(_l), r(_r), y(0, MAX),
    lc(NULL), rc(NULL) {}
  };
  typedef node* pnode;

  pnode root;

  Segtree2D(int l, int r) {
    root = new node(l, r);
  }

  void update(pnode& nw, int x, int y, int val) {
    int& l = nw->l, &r = nw->r, mid = (l + r) / 2;
    if(l == r)
      nw->y.update(y, val);
    else {
      if(x <= mid) {
        if(!nw->lc)
          nw->lc = new node(l, mid);
        update(nw->lc, x, y, val);
      } else {
        if(!nw->rc)
          nw->rc = new node(mid + 1, r);
        update(nw->rc, x, y, val);
      }
      val = min(nw->lc ? nw->lc->y.query(y, y) : INF,
                nw->rc ? nw->rc->y.query(y, y) : INF);
      nw->y.update(y, val);
    }
  }

  int query(pnode& nw, int x1, int x2, int y1, int y2) {
    if(!nw)
      return INF;
    int& l = nw->l, &r = nw->r;
    if(r < x1 || x2 < l)
      return INF;
    if(x1 <= l && r <= x2)
      return nw->y.query(y1, y2);
    int ret = min(query(nw->lc, x1, x2, y1, y2),
                  query(nw->rc, x1, x2, y1, y2));
    return ret;
  }

  void update(int x, int y, int val) {
    assert(root->l <= x && x <= root->r);
    update(root, x, y, val);
  }

  int query(int x1, int x2, int y1, int y2) {
    return query(root, x1, x2, y1, y2);
  }
};
