using ld = double; // change to long double if reach 10^18
using cd = complex<ld>;
const ld PI = acos(-(ld)1);

void fft(vector<cd> &a, int sign = 1)
{
    int n = a.size();
    ld theta = sign * 2 * PI / n;
    for(int i = 0, j = 1; j < n-1; j++)
    {
        for(int k = n >> 1; k > (i ^= k); k >>= 1);
        if(j < i) swap(a[i], a[j]);
    }
    for(int m, mh = 1; (m = mh << 1) <= n; mh = m)
    {
        int irev = 0;
        for(int i = 0; i < n; i += m)
        {
            cd w = exp(cd(0, theta*irev));
            for(int k = n >> 2; k > (irev ^= k); k >>= 1);
            for(int j = i; j < mh + i; j++)
            {
                int k = j+mh;
                cd x = a[j] - a[k];
                a[j] += a[k];
                a[k] = w * x;
            }
        }
    }
    if(sign == -1) for(cd &i : a) i /= n;
}

vector<ll> multiply(vector<ll> const& a, vector<ll> const &b)
{
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while(n < a.size() + b.size()) n <<= 1;
    fa.resize(n); fb.resize(n);
    fft(fa); fft(fb);
    for(int i = 0; i < n; i++) fa[i] *= fb[i];
    fft(fa, -1);
    vector<ll> res(n);
    for(int i = 0; i < n; i++) res[i] = round(fa[i].real());
    return res;
}
