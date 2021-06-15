// stores result in sa and lcp
// if lcp is needed, call SuffixArray(str, 1)
struct SuffixArray
{
    int n;
    vector<int> sa, lcp, rnk, cnt;
    vector<pair<int, int>> p;
    SuffixArray(const string& s, bool calc_lcp = 0) :
        n(s.length() + 1), sa(n), lcp(calc_lcp ? n : 0), rnk(n << 1),
        cnt(max(n, 256)), p(n)
    {
        for(int i = 0; i < n - 1; ++i) rnk[i] = s[i];
        rnk[n - 1] = 0;
        iota(sa.begin(), sa.end(), 0);
        for(int i = 1; i < n; i <<= 1) update_sa(i);
        if(!calc_lcp) return;
        vector<int> phi(n), plcp(n);
        phi[sa[0]] = -1;
        for(int i = 1; i < n; ++i) phi[sa[i]] = sa[i - 1];
        int l = 0;
        for(int i = 0; i < n; ++i)
        {
            if(phi[i] == -1) plcp[i] = 0;
            else
            {
                while((i + l < n) && (phi[i] + l < n)
                      && (s[i + l] == s[phi[i] + l])) ++l;
                plcp[i] = l;
                l = max(l - 1, 0);
            }
        }
        for(int i = 0; i < n; ++i) lcp[i] = plcp[sa[i]];
    }
    void update_sa(int len)
    {
        sort_sa(len); sort_sa(0);
        for(int i = 0; i < n; ++i) p[i] = {rnk[i], rnk[i + len]};
        auto lst = p[sa[0]];
        rnk[sa[0]] = 0;
        int cur = 0;
        for(int i = 1; i < n; ++i)
        {
            if(lst != p[sa[i]])
            {
                lst = p[sa[i]];
                ++cur;
            }
            rnk[sa[i]] = cur;
        }
    }
    void sort_sa(int offset)
    {
        fill(cnt.begin(), cnt.end(), 0);
        for(int i = 0; i < n; ++i) ++cnt[rnk[i + offset]];
        int sum = 0;
        for(int i = 0; i < (int) cnt.size(); ++i)
        {
            int temp = cnt[i];
            cnt[i] = sum;
            sum += temp;
        }
        vector<int> temp(n);
        for(int i = 0; i < n; ++i)
        {
            int cur = cnt[rnk[sa[i] + offset]]++;
            temp[cur] = sa[i];
        }
        sa = move(temp);
    }
};
