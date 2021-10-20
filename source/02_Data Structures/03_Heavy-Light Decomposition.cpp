struct HLD {
  int n;
  vector<int> id, size, idx, up, root, st;
  vector<vector<int>> adj, chain;
  SegTree seg;

  HLD(const vector<vector<int>>& edges) :
    n(edges.size()), id(n, -1), size(n, -1), idx(n, -1),
    up(n, -1), adj(edges), seg(n) {
    precompute(0, -1);
    decompose(0, -1);
    int cnt = 0;
    st.resize(chain.size());
    for(int i = 0; i < (int) chain.size(); ++i) {
      st[i] = cnt;
      cnt += chain[i].size();
    }
  }

  void precompute(int pos, int dad) {
    size[pos] = 1;
    up[pos] = dad;
    for(auto& i : adj[pos]) {
      if(i != dad) {
        precompute(i, pos);
        size[pos] += size[i];
      }
    }
  }

  void decompose(int pos, int dad) {
    if(id[pos] == -1) {
      id[pos] = chain.size();
      root.push_back(pos);
      chain.emplace_back();
    }
    idx[pos] = chain[id[pos]].size();
    chain[id[pos]].push_back(pos);
    int mx = 0, heavy = -1;
    for(auto& i : adj[pos]) {
      if(i != dad && size[i] > mx) {
        mx = size[i];
        heavy = i;
      }
    }
    if(heavy != -1)
      id[heavy] = id[pos];
    for(auto& i : adj[pos]) {
      if(i != dad)
        decompose(i, pos);
    }
  }

  void update(int ch, int l, int r, int val) {
    seg.update(st[ch] + l, st[ch] + r, val);
  }

  int query(int ch, int l, int r, int val) {
    return seg.query(st[ch] + l, st[ch] + r, val);
  }
};

// how to move from u to v
while(1) {
  if(hld.id[u] == hld.id[v]) {
    if(hld.idx[u] > hld.idx[v])
      swap(u, v);
    hld.update(hld.id[u], hld.idx[u], hld.idx[v], w);
    // or hld.query(hld.id[u], hld.idx[u], hld.idx[v]);
    break;
  }
  if(hld.id[u] < hld.id[v])
    swap(u, v);
  hld.update(hld.id[u], 0, hld.idx[u], w);
  // or hld.query(hld.id[u], 0, hld.idx[v]);
  u = hld.up[hld.root[hld.id[u]]];
}
