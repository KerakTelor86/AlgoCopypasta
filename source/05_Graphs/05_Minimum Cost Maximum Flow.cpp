using FlowT = ll;
using CostT = ll;

const FlowT F_INF = 1e18;
const CostT C_INF = 1e18;
const int MAX_V = 1e5 + 5;
const int MAX_E = 1e6 + 5;

namespace MCMF {
  int n, E;
  int adj[MAX_E], nxt[MAX_E], lst[MAX_V], frm[MAX_V], vis[MAX_V];
  FlowT cap[MAX_E], flw[MAX_E], totalFlow;
  CostT cst[MAX_E], dst[MAX_V], totalCost;

  void init(int _n) {
    n = _n;
    fill_n(lst, n, -1), E = 0;
  }
  void add(int u, int v, FlowT ca, CostT co) {
    adj[E] = v, cap[E] = ca, flw[E] = 0, cst[E] = +co;
    nxt[E] = lst[u], lst[u] = E++;
    adj[E] = u, cap[E] =  0, flw[E] = 0, cst[E] = -co;
    nxt[E] = lst[v], lst[v] = E++;
  }
  int spfa(int s, int t) {
    fill_n(dst, n, C_INF), dst[s] = 0;
    queue<int> que;
    que.push(s);
    while(que.size()) {
      int u = que.front();
      que.pop();
      for(int e = lst[u]; e != -1; e = nxt[e])
        if(flw[e] < cap[e]) {
          int v = adj[e];
          if(dst[v] > dst[u] + cst[e]) {
            dst[v] = dst[u] + cst[e];
            frm[v] = e;
            if(!vis[v]) {
              vis[v] = 1;
              que.push(v);
            }
          }
        }
      vis[u] = 0;
    }
    return dst[t] < C_INF;
  }
  pair<FlowT, CostT> solve(int s, int t) {
    totalCost = 0, totalFlow = 0;
    while(1) {
      if(!spfa(s, t))
        break;
      FlowT mn = F_INF;
      for(int v = t, e = frm[v]; v != s; v = adj[e ^ 1], e = frm[v])
        mn = min(mn, cap[e] - flw[e]);
      for(int v = t, e = frm[v]; v != s; v = adj[e ^ 1], e = frm[v]) {
        flw[e] += mn;
        flw[e ^ 1] -= mn;
      }
      totalFlow += mn;
      totalCost += mn * dst[t];
    }
    return {totalFlow, totalCost};
  }
};
