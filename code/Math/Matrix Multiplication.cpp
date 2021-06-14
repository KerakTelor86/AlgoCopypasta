using Mat = vector<vector<ll>>;

Mat multiply(const Mat& a, const Mat& b)
{
    assert(a[0].size() == b.size());
    int y = a.size(), x = b[0].size(), n = b.size();
    Mat res(y, vector<ll>(x));
    for(int i = 0; i < y; ++i)
        for(int k = 0; k < n; ++k)
            for(int j = 0; j < x; ++j)
                res[i][j] += a[i][k] * b[k][j];
    return res;
}
