
#define N 300020
vector<int> adj[N];
int memo[25][N], lvl[N], subsize[N], col[N]; //col=array input
int chainHead[N], chainInd[N], baseArray[N], posInBase[N]; 
int chainNo, p, n;//chainHead=nodeHead,baseArray=array tree, int st[N*4]; //posInBase=convert input to tree indelax
void buildtree(int v, int l, int r){
    if (l == r){
        st[v] = baseArray[l];
        return;
    }
    int m = (l+r)>>1;
    buildtree(v<<1,l,m);
    buildtree(v<<1|1,m+1,r);
    st[v] = st[v<<1]+st[v<<1|1];
}

void updatetree(int v, int l, int r, int x){
    if(l == r){
        st[v] = baseArray[x]; return;
    }
    int m = (l+r)>>1;
    if(x <= m) updatetree(v<<1,l,m,x);
    else updatetree(v<<1|1,m+1,r,x);
    st[v] = st[v<<1]+st[v<<1|1];
}
int querytree(int v, int l, int r, int ss, int se){
    if(ss > se) return 0;
    if (l == ss && r == se) return st[v];
    int m = (l+r)>>1;
    int ans = querytree(v << 1, l, m, ss, min(se,m)) + querytree(v << 1|1, m+1, r, max(m+1,ss), se);
    return ans;
}
void dfs(int cur, int par){
    lvl[cur] = lvl[par]+1;
    memo[0][cur] = par;
    subsize[cur] = 1;
    for(int to : adj[cur]){
        if (to == par) continue;
        dfs(to,cur);
        subsize[cur] += subsize[to];
    }
}
void HLD(int cur, int par){
    if(chainHead[chainNo] == -1) chainHead[chainNo] = cur;
    chainInd[cur] = chainNo;
    baseArray[p] = col[cur];
    posInBase[cur] = p++;
    int maksto = -1;
    for(int to : adj[cur]){
        if (to == par) continue;
        if (maksto == -1 || subsize[maksto] < subsize[to]){
            maksto = to;
        }
    }
    if (maksto != -1) HLD(maksto,cur);
    for(int to : adj[cur]){
        if (to == par || to == maksto) continue;
        chainNo++;
        HLD(to,cur);				
    }
}
int queryup(int u, int v){
    int ans = 0;
    while(u != v){
        if (chainInd[u] == chainInd[v]){
            ans += querytree(1,0,n-1,posInBase[v]+1,posInBase[u]);
            break;
        } else {
            ans += querytree(1,0,n-1, posInBase[chainHead[chainInd[u]]] ,posInBase[u]);
            u = chainHead[chainInd[u]];
            u = memo[0][u];
        }		
    }
    return ans;
}

int main()
{
    rep(i,0,n-1){ //init	
        col[i] = s[i]-'0';
        chainHead[i] = -1;
        adj[i].clear();
    }
    chainNo = p = 0;
    // add edge here
    dfs(0,0); // 0-based
    sparsing();
    HLD(0,0);
    buildtree(1,0,n-1);
    return 0;
}
