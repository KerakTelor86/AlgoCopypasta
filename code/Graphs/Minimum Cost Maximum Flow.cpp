// 1-based index
template<class T>
using rpq = priority_queue<T, vector<T>, greater<T>>;

const ll INF = 1e18;

struct MCMF
{
    struct Edge
    {
        int v;
        ll cap, cost;
        int rev;
        Edge(int _v, ll _cap, ll _cost, int _rev) :
            v(_v), cap(_cap), cost(_cost), rev(_rev) {}
    };

    ll flow, cost;
    int st, ed, n;
    vector<ll> dist, H;
    vector<int> pv, pe;
    vector<vector<Edge>> adj;

    bool dijkstra()
    {
        rpq<pair<ll, int>> pq;
        dist.assign(n + 1, INF);
        dist[st] = 0;
        pq.emplace(0, st);
        while(!pq.empty())
        {
            auto [cst, pos] = pq.top();
            pq.pop();
            if(dist[pos] < cst) continue;
            for(int i = 0; i < (int) adj[pos].size(); ++i)
            {
                auto& e = adj[pos][i];
                int nxt = e.v;
                ll nxt_cst = dist[pos] + e.cost + H[pos] - H[nxt];
                if(e.cap > 0 && nxt_cst < dist[nxt])
                {
                    dist[nxt] = nxt_cst;
                    pe[nxt] = i;
                    pv[nxt] = pos;
                    pq.emplace(nxt_cst, nxt);
                }
            }
        }
        return dist[ed] != INF;
    }

    MCMF(int _n) : n(_n), pv(n + 1), pe(n + 1), adj(n + 1) {}

    void add_edge(int u, int v, ll cap, ll cst)
    {
        adj[u].emplace_back(v, cap, cst, adj[v].size());
        adj[v].emplace_back(u, 0, -cst, adj[u].size() - 1);
    }

    pair<ll, ll> solve(int _st, int _ed)
    {
        st = _st;
        ed = _ed;
        flow = 0;
        cost = 0;
        H.assign(n + 1, 0);
        while(dijkstra())
        {
            for(int i = 0; i <= n; ++i)
                H[i] += dist[i];
            ll f = INF;
            for(int i = ed; i != st; i = pv[i])
                f = min(f, adj[pv[i]][pe[i]].cap);
            flow += f;
            cost += f * H[ed];
            for(int i = ed; i != st; i = pv[i])
            {
                auto& e = adj[pv[i]][pe[i]];
                e.cap -= f;
                adj[i][e.rev].cap += f;
            }
        }
        return {flow, cost};
    }
};
