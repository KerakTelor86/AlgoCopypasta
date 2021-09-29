
template<typename T>
T extended_euclid(T a, T b, T &x, T &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    T xx, yy, gcd;
    gcd = extended_euclid(b, a % b, xx, yy);
    x = yy;
    y = xx - (yy * (a / b));
    return gcd;
}
template<typename T>
T MOD(T a, T b) { return (a%b + b) % b; }
// return x, lcm. x = a % n && x = b % m
template<typename T>
pair<T,T> CRT(T a, T n, T b, T m) {
    T _n, _m;
    T gcd = extended_euclid(n, m, _n, _m);
    if (n == m) {
        if (a == b) return pair<T,T>(a, n);
        else return pair<T,T>(-1, -1);
    } else if (abs(a-b) % gcd != 0) return pair<T,T>(-1, -1);
    else {
        T lcm = m * n / gcd;
        T x = MOD(a + MOD(n*MOD(_n*((b-a)/gcd), m/gcd), lcm), lcm);
        return pair<T,T>(x, lcm);
    }}
