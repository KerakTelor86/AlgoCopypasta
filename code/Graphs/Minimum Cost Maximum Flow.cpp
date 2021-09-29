struct Edge{ int from, to, capacity, cost; };
vector<vector<int>> adja;
vector<vector<ll>> cost, capacity;
void shortest_paths(int n, int v0, vector<ll>& d, vector<ll>& p) {
    d.assign(n, INF);
    d[v0] = 0;
    bool inq[n]={false};
    queue<int> q;
    q.push(v0);
    p.assign(n, -1);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        inq[u] = false;
        for (int v : adja[u]) {
            if (capacity[u][v] > 0 && d[v] > d[u] + cost[u][v]) {
                d[v] = d[u] + cost[u][v]; p[v] = u;
                if (!inq[v]) { inq[v] = true; q.push(v); }
            }
        }
    }
}
ll min_cost_flow(int Ns, int K) { // Ns=jmlh node, K=expectedflow
    adja.assign(Ns, vector<int>());
    cost.assign(Ns, vector<ll>(Ns, 0));
    capacity.assign(Ns, vector<ll>(Ns, 0));
    int t=Ns-1, s=Ns-2;
    // add edge disini
    adja[/*sumber*/].pb(/*target*/); adja[/*target*/].pb(/*sumber*/);
    cost[/*sumber*/][/*target*/]=0; cost[/*target*/][/*sumber*/] = 0;
    capacity[/*sumber*/][/*target*/] = more[i].se;
    int flow = 0;
    ll cost = 0;
    vector<ll> d, p;
    while (flow < K) {
        shortest_paths(Ns, s, d, p);
        if (d[t] == INF) break;
        ll f = K - flow;  // find max flow on that path
        int cur = t;
        while (cur != s) {
            f = min(f, capacity[p[cur]][cur]);
            cur = p[cur];
        }    
        flow += f; // apply flow
        cost += f * d[t];
        cur = t;
        while (cur != s) {
            capacity[p[cur]][cur] -= f;
            capacity[cur][p[cur]] += f;
            cur = p[cur];
        }
    }  
    if (flow < K) return -1; else return cost;
}
