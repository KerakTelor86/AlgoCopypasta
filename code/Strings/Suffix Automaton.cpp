struct state {
    int len, link;
    map<char,int>next;//use array if TLE
};

const int MAXLEN = 100005;
state st[MAXLEN*2];
int sz, last;

void sa_init() {
    sz = last = 0;
    st[0].len = 0;
    st[0].link = -1;
    st[0].next.clear();
    ++sz;
}

void sa_extend (char c) {
    int cur = sz++;
    st[cur].len = st[last].len + 1;
    st[cur].next.clear();
    int p;
    for (p=last; p!=-1 && !st[p].next.count(c); p=st[p].link)
        st[p].next[c] = cur;
    if (p == -1)
        st[cur].link = 0;
    else {
        int q = st[p].next[c];
        if (st[p].len + 1 == st[q].len)
            st[cur].link = q;
        else {
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            st[clone].next = st[q].next;
            st[clone].link = st[q].link;
            for (; p!=-1 && st[p].next[c]==q; p=st[p].link)
                st[p].next[c] = clone;
            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;
}

// forwarding
for ( int i = 0; i < m; i++ ){
    while ( cur >= 0 && st[cur].next.count(pa[i]) == 0 ){
        cur = st[cur].link;
        if ( cur != -1 )
            len = st[cur].len;
    }
    if ( st[cur].next.count(pa[i]) ){
        len++;
        cur = st[cur].next[pa[i]];
    } else len = cur = 0;
}

// shortening abc -> bc
if ( l == m ){
    l--;
    if ( l <= st[st[cur].link].len )
        cur = st[cur].link;
}

// finding lowest and highest length
int lo = st[st[cur].link].len+1;
int hi = st[cur].len;

//Finding number of distinct substrings
//answer = distsub(0)
LL d[MAXLEN*2];
LL distsub(int ver)
{
    LL  tp = 1;
    if(d[ver]) return d[ver];

    for(map<char, int>::iterator it=st[ver].next.begin();it!=st[ver].next.end();it++)
    {
        tp+=distsub(it->second);
    }
    d[ver]=tp;
    return d[ver];
}

//Total Length of all distinct substrings
//call distsub first before call lesub
LL ans[MAXLEN*2];
LL lesub(int ver)
{
    LL tp=0;
    if(ans[ver]) return ans[ver];
    for(map<char, int>::iterator it=st[ver].next.begin();it!=st[ver].next.end();it++)
    {
        tp+=lesub(it->second)+d[it->second];
    }
    ans[ver]=tp;
    return ans[ver];
}
//find the k-th lexicographical substring
void kthsub(int ver, int K, string &ret)
{
    for(map<char, int>::iterator it=st[ver].next.begin();it!=st[ver].next.end();it++)
    {
        int v=it->second;
        if(K<=d[v])
        {
            K--;
            if(K==0)
            {
                ret.push_back(it->first);
                return;
            }
            else
            {
                ret.push_back(it->first);
                kthsub(v, K, ret);
                return;
            }
        }
        else
        {
            K-=d[v];
        }
    }
}
// Smallest Cyclic Shift to obtain lexicographical smallest of All possible
//in int main do this
int main()
{
    string S;
    sa_init();
    cin>>S;//input
    tp=0;
    t=S.length();
    S+=S;
    for(int a=0;a<S.size();a++)
    {
        sa_extend(S[a]);
    }
    minshift(0);
}
//the function
int tp, t;
void minshift(int ver)
{
    for(map<char, int>::iterator it=st[ver].next.begin();it!=st[ver].next.end();it++)
    {
        tp++;
        if(tp==t)
        {
            cout<<st[ver].len - t +1<<endl;
            break;
        }
        minshift(it->second);
        break;
    }
}
//end of function



// LONGEST COMMON SUBSTRING OF TWO STRINGS
string lcs (string s, string t) {
    sa_init();
    for (int i=0; i<(int)s.length(); ++i)
        sa_extend (s[i]);

    int v = 0,  l = 0,
        best = 0,  bestpos = 0;
    for (int i=0; i<(int)t.length(); ++i) {
        while (v && ! st[v].next.count(t[i])) {
            v = st[v].link;
            l = st[v].length;
        }
        if (st[v].next.count(t[i])) {
            v = st[v].next[t[i]];
            ++l;
        }
        if (l > best)
            best = l,  bestpos = i;
    }
    return t.substr (bestpos-best+1, best);
}
