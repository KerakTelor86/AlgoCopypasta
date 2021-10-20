// Maximum matching on general graphs in O(V^2 E)
// Indices are 1-based
// Stolen from ko_osaga's cheatsheet
struct Blossom {
  vector<int> vis, dad, orig, match, aux;
  vector<vector<int>> conn;
  int t, N;
  queue<int> Q;

  void augment(int u, int v) {
    int pv = v;
    do {
      pv = dad[v];
      int nv = match[pv];
      match[v] = pv;
      match[pv] = v;
      v = nv;
    } while(u != pv);
  }

  int lca(int v, int w) {
    ++t;
    while(true) {
      if(v) {
        if(aux[v] == t)
          return v;
        aux[v] = t;
        v = orig[dad[match[v]]];
      }
      swap(v, w);
    }
  }

  void blossom(int v, int w, int a) {
    while(orig[v] != a) {
      dad[v] = w;
      w = match[v];
      if(vis[w] == 1) {
        Q.push(w);
        vis[w] = 0;
      }
      orig[v] = orig[w] = a;
      v = dad[w];
    }
  }

  bool bfs(int u) {
    fill(vis.begin(), vis.end(), -1);
    iota(orig.begin(), orig.end(), 0);
    Q = queue<int>();
    Q.push(u);
    vis[u] = 0;
    while(!Q.empty()) {
      int v = Q.front();
      Q.pop();
      for(int x : conn[v]) {
        if(vis[x] == -1) {
          dad[x] = v;
          vis[x] = 1;
          if(!match[x]) {
            augment(u, x);
            return 1;
          }
          Q.push(match[x]);
          vis[match[x]] = 0;
        } else if(vis[x] == 0 && orig[v] != orig[x]) {
          int a = lca(orig[v], orig[x]);
          blossom(x, v, a);
          blossom(v, x, a);
        }
      }
    }
    return false;
  }

  Blossom(int n) : // n = vertices
    vis(n + 1), dad(n + 1), orig(n + 1), match(n + 1),
    aux(n + 1), conn(n + 1), t(0), N(n) {
    for(int i = 0; i <= n; ++i) {
      conn[i].clear();
      match[i] = aux[i] = dad[i] = 0;
    }
  }

  void add_edge(int u, int v) {
    conn[u].push_back(v);
    conn[v].push_back(u);
  }

  int solve() { // call this for answer
    int ans = 0;
    vector<int> V(N - 1);
    iota(V.begin(), V.end(), 1);
    shuffle(V.begin(), V.end(), mt19937(0x94949));
    for(auto x : V) {
      if(!match[x]) {
        for(auto y : conn[x]) {
          if(!match[y]) {
            match[x] = y, match[y] = x;
            ++ans;
            break;
          }
        }
      }
    }
    for(int i = 1; i <= N; ++i) {
      if(!match[i] && bfs(i))
        ++ans;
    }
    return ans;
  }
};
