const int M=530010+5;
inline int fastex(int x, int y) {
    int ret = 1;
    while(y) {
        if(y & 1) ret = 1ll * ret * x % MOD;
        x = 1ll * x * x % MOD; y >>= 1;
    }
    return ret;
}
int rev[M], w[M], g[M],h[M], f[M], l[M];
inline void NTT(int *a, int N) {
    for(int i = 0; i < N; ++ i) {
        if(rev[i] > i) {
            swap(a[rev[i]], a[i]);
        }
    }
    for(int d = 1, t = (N >> 1); d < N; d <<= 1, t >>= 1) {
        for(int i = 0; i < N; i += (d << 1)) {
            for(int j = 0; j < d; ++ j) {
                int tmp = 1ll * w[t * j] * a[i + j + d] % MOD;
                a[i + j + d] = a[i + j] - tmp + MOD; if(a[i + j + d] >= MOD) a[i + j + d] -= MOD;
                a[i + j] = a[i + j] + tmp; if(a[i + j] >= MOD) a[i + j] -= MOD;
            }
        }
    }
}
inline void get_mul(int *f, int *g, int n, int m, int is_inv) {
    static int a[M], b[M];
    int N = 1, L = 0;
    for(; N < (n + m); N <<= 1, ++ L);
    for(int i = 1; i < N; ++ i) {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1));
    }
    w[0] = 1; w[1] = fastex(3, (MOD - 1) / N);
    for(int i = 2; i < N; ++ i) {
        w[i] = 1ll * w[i - 1] * w[1] % MOD;
    }
    for(int i = 0; i < N; ++ i) {
        a[i] = b[i] = 0;
    }
    for(int i = 0; i < n; ++ i) {
        a[i] = f[i];
    }
    for(int i = 0; i < m; ++ i) {
        b[i] = g[i];
    }
    NTT(a, N), NTT(b, N);
    for(int i = 0; i < N; ++ i) {
        if(is_inv) {
            a[i] = 1ll * b[i] * (2ll - 1ll * a[i] * b[i] % MOD + MOD) % MOD;
        }
        else {
            a[i] = 1ll * a[i] * b[i] % MOD;
        }
    }
    w[1] = fastex(w[1], MOD - 2);
    for(int i = 2; i < N; ++ i) {
        w[i] = 1ll * w[i - 1] * w[1] % MOD;
    }
    NTT(a, N);
    int inv = fastex(N, MOD - 2);
    for(int i = 0; i < n; ++ i) {
        a[i] = 1ll * a[i] * inv % MOD;
    }
    for(int i = 0; i < n; ++ i) {
        if(is_inv) g[i] = a[i];
        else f[i] = a[i];
    }
}
inline void get_inv(int *f, int *g, int n) {
    if(n == 1) {
        g[0] = fastex(f[0], MOD - 2);
        return;
    }
    get_inv(f, g, (n + 1) / 2);
    get_mul(f, g, n, n, 1);
}
inline void get_deri(int *f, int *g, int n) {
    for(int i = 1; i < n; ++ i) {
        g[i - 1] = 1ll * f[i] * i % MOD;
    }
    g[n - 1] = 0;
}
inline void get_inte(int *f, int *g, int n) {
    for(int i = 1; i < n; ++ i) {
        g[i] = 1ll * f[i - 1] * fastex(i, MOD - 2) % MOD;
    }
    g[0] = 0;
}
inline void get_ln(int *f, int *g, int n) {
    static int a[M], b[M];
    for(int i = 0; i < n; ++ i) a[i] = b[i] = 0;
    get_deri(f, a, n); get_inv(f, b, n);
    get_mul(a, b, n, n, 0);
    get_inte(a, g, n);
}
inline void get_exp(int *f, int *g, int n) {
    static int a[M], b[M];
    for(int i = 0; i < n; ++ i) a[i] = b[i] = 0;
    if(n == 1) {
        g[0] = 1;
        return;
    }
    get_exp(f, g, (n + 1) / 2);
    get_ln(g, a, n);
    for(int i = 0; i < n; ++ i) {
        b[i] = (f[i] - a[i] + MOD);
        if(b[i] >= MOD) b[i] -= MOD;
    }
    b[0] ++; if(b[0] >= MOD) b[0] -= MOD;
    get_mul(g, b, n, n, 0);
}
inline void get_pow(int *f, int *g, int n, int k, int k1) {
    static int a[M], b[M];
    int t = -1;
    for(int i = 0; i < n; ++ i) {
        if(f[i] != 0) {
            t = i;
            break;
        }
    }
    if(t == -1) {
        for(int i = 0; i < n; ++ i) {
            g[i] = 0;
        }
        return;
    }
    int inv = fastex(f[t], MOD - 2), pp = fastex(f[t], k1);
    for(int i = 0; i < n; ++ i) {
        a[i] = b[i] = 0;
    }
    for(int i = 0; i < n - t; ++ i) {
        b[i] = 1ll * f[i + t] * inv % MOD;
    }
    get_ln(b, a, n);
    for(int i = 0; i < n; ++ i) {
        a[i] = 1ll * a[i] * k % MOD;
    }
    get_exp(a, g, n);
    int lim = min(1ll * t * k, 1ll * n);
    for(int i = n - 1; i >= lim; -- i) {
        g[i] = 1ll * g[i - 1ll * t * k] * pp % MOD;
    }
    for(int i = 0; i < lim; ++ i) {
        g[i] = 0;
    }
}
