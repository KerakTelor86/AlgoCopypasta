struct SuffixArray
{
    int n;
    vector<int> sa, rnk, cnt;
    vector<pair<int, int>> p;
    SuffixArray(const string& s) :
        n(s.length() + 1), sa(n), rnk(n << 1), cnt(max(n, 256)), p(n)
    {
        for(int i = 0; i < n - 1; ++i) rnk[i] = s[i];
        rnk[n - 1] = 0;
        iota(sa.begin(), sa.end(), 0);
        for(int i = 1; i < n; i <<= 1) update(i);
    }
    void update(int len)
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
    const int& operator[](int idx) const
    {
        return sa[idx];
    }
};
