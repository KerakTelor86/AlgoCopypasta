// O(VE log(max_flow)) if scaling == 1
// O((V + E) sqrt(E)) if unit graph (turn scaling off)
// O((V + E) sqrt(V)) if bipartite matching (turn scaling off)
// indices are 0-based
const ll INF = 1e18;

struct Dinic
{ 
    struct Edge
    {
        int v;
        ll cap, flow;
        Edge(int _v, ll _cap) : v(_v), cap(_cap), flow(0) {}
    };

    int n;
    ll lim;
    vector<vector<int>> gr;
    vector<Edge> e;
    vector<int> idx, lv;

    bool has_path(int s, int t)
    {
        queue<int> q;
        q.push(s);
        lv.assign(n, -1);
        lv[s] = 0;
        while(!q.empty())
        {
            int c = q.front();
            q.pop();
            if(c == t) break;
            for(auto& i : gr[c])
            {
                ll cur_flow = e[i].cap - e[i].flow;
                if(lv[e[i].v] == -1 && cur_flow >= lim)
                {
                    lv[e[i].v] = lv[c] + 1;
                    q.push(e[i].v);
                }
            }
        }
        return lv[t] != -1;
    }

    ll get_flow(int s, int t, ll left)
    {
        if(!left || s == t) return left;
        while(idx[s] < (int) gr[s].size())
        {
            int i = gr[s][idx[s]];
            if(lv[e[i].v] == lv[s] + 1)
            {
                ll add = get_flow(
                    e[i].v,
                    t,
                    min(left, e[i].cap - e[i].flow)
                );
                if(add)
                {
                    e[i].flow += add;
                    e[i ^ 1].flow -= add;
                    return add;
                }
            }
            ++idx[s];
        }
        return 0;
    }

    Dinic(int vertices, bool scaling = 1) // toggle scaling here
        : n(vertices), lim(scaling ? 1 << 30 : 1), gr(n) {}

    void add_edge(int from, int to, ll cap, bool directed = 1)
    {
        gr[from].push_back(e.size());
        e.emplace_back(to, cap);
        gr[to].push_back(e.size());
        e.emplace_back(from, directed ? 0 : cap);
    }

    ll get_max_flow(int s, int t) // call this
    {
        ll res = 0;
        while(lim) // scaling
        {
            while(has_path(s, t))
            {
                idx.assign(n, 0);
                while(ll add = get_flow(s, t, INF)) res += add;
            }
            lim >>= 1;
        }
        return res;
    }
};
