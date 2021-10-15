namespace FFT {
    /* ----- Adjust the constants here ----- */
    const int LN = 24; //23
    const int N = 1 << LN;
    typedef long long LL; // 2**23 * 119 + 1. 998244353
    // `MOD` must be of the form 2**`LN` * k + 1, where k odd.
    const LL MOD = 9223372036737335297; // 2**24 * 54975513881 + 1.
    const LL PRIMITIVE_ROOT = 3; // Primitive root modulo `MOD`.
    /* ----- End of constants ----- */
    LL root[N];
    inline LL power(LL x, LL y) {
        LL ret = 1;
        for (; y; y >>= 1) {
            if (y & 1) ret = (__int128) ret * x % MOD;
            x = (__int128) x * x % MOD;
        }
        return ret;
    }
    inline void init_fft() {
        const LL UNITY = power(PRIMITIVE_ROOT, MOD-1 >> LN);
        root[0] = 1;
        for (int i=1; i<N; i++) {
            root[i] = (__int128) UNITY * root[i-1] % MOD;
        }return;
    }
    // n = 2^k is the length of polynom
    inline void fft(int n, vector<LL> &a, bool invert) {
        for (int i=1, j=0; i<n; ++i) {
            int bit = n >> 1;
            for (; j>=bit; bit>>=1) j -= bit;
            j += bit;
            if (i < j) swap(a[i], a[j]);
        }
        for (int len=2; len<=n; len<<=1) {
            LL wlen = (invert ? root[N - N/len] : root[N/len]);
            for (int i=0; i<n; i+=len) {
                LL w = 1;
                for (int j=0; j<len>>1; j++) {
                    LL u = a[i+j];
                    LL v = (__int128) a[i+j + len/2] * w % MOD;
                    a[i+j] = ((__int128) u + v) % MOD;
                    a[i+j + len/2] = ((__int128) u - v + MOD) % MOD;
                    w = (__int128) w * wlen % MOD;
                }
            }
        }
        if (invert) {
            LL inv = power(n, MOD-2);
            for (int i=0; i<n; i++) a[i] = (__int128) a[i] * inv % MOD;
        }return;
    }
    inline vector<LL> multiply(vector<LL> a, vector<LL> b) {
        vector<LL> c;
        int len = 1 << 32 - __builtin_clz(a.size() + b.size() - 2);
        a.resize(len, 0); b.resize(len, 0);
        fft(len, a, false); fft(len, b, false);
        c.resize(len);
        for (int i = 0; i < len; ++i)c[i] = (__int128) a[i]*b[i]%MOD; 
        fft(len, c, true);
        return c;
    }
    //FFT::init_fft(); wajib di panggil init di awal
}
