template <typename TD> struct Hungarian {
    TD INF = 1e9;  //max_inf
    int n; vector<vector<TD> > adj; // cost[left][right]
    vector<TD> hl,hr,slk;
    vector<int> fl,fr,vl,vr,pre;
    deque<int> q;
    Hungarian(int _n) {
        n=_n; adj = vector<vector<TD> >(n, vector<TD> (n, 0));
    }
    int check(int i) {
        if (vl[i]=1,fl[i]!=-1) return q.push_back(fl[i]), vr[fl[i]]=1;
        while (i!=-1) swap(i,fr[fl[i]=pre[i]]); return 0;
    }
    void bfs(int s) {
        slk.assign(n,INF); vl.assign(n,0); vr=vl; q.assign(vr[s]=1,s);
        for (TD d;;) {
            for (;!q.empty();q.pop_front()) {
                for (int i=0,j=q.front();i<n;i++) {
                    if (d=hl[i]+hr[j]-adj[i][j],!vl[i]&&d<=slk[i]) {
                        if (pre[i]=j,d) slk[i]=d; else if (!check(i)) return;    
                    }}}
            d=INF;
            for (int i = 0; i < n; i++) if (!vl[i]&&d>slk[i]) d=slk[i];
            for (int i = 0; i < n; i++) {
                if (vl[i]) hl[i]+=d; else slk[i]-=d;
                if (vr[i]) hr[i]-=d;
            }
            for (int i = 0; i < n; i++) if (!vl[i]&&!slk[i]&&!check(i)) return;
        }}
    TD solve() {
        fl.assign(n,-1); fr=fl; hl.assign(n,0); hr=hl; pre.assign(n,0);
        for (int i = 0; i < n; i++) hl[i]=*max_element(adj[i].begin(),adj[i].begin()+n);
        for (int i = 0; i < n; i++) bfs(i);
        TD ret=0;
        for (int i = 0; i < n; i++) if (adj[i][fl[i]]) ret+=adj[i][fl[i]];
        return ret;
    }
}; //i wiLL be matched with fl[i]
