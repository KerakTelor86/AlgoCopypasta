#define N 10020
vector<int> adj[N];
bool vis[N], ins[N];
int disc[N], low[N], gr[N];
stack<int> st;
int id,grid;
void scc(int cur, int par)
{
    disc[cur]=low[cur]=++id;
    vis[cur]=ins[cur]=1;
    st.push(cur);
    for(int to : adj[cur])
    {
        //if (to==par) continue; // ini untuk SO(scc undirected)
        if (!vis[to]) scc(to,cur);
        if (ins[to]) low[cur]=min(low[cur],low[to]);	
    }	
    if(low[cur]==disc[cur])
    {
        grid++; // group id		
        while(ins[cur])
        {
            gr[st.tp]=grid; ins[st.tp]=0; st.pop();
        }	
    }
}
