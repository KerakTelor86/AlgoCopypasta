namespace MillerRabin {
  const vector<ll> primes = { // deterministic up to 2^64 - 1
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37
  };
  ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
  }
  ll powa(ll x, ll y, ll p) { // (x ^ y) % p
    if(!y)
      return 1;
    if(y & 1)
      return ((__int128) x * powa(x, y - 1, p)) % p;
    ll temp = powa(x, y >> 1, p);
    return ((__int128) temp * temp) % p;
  }
  bool miller_rabin(ll n, ll a, ll d, int s) {
    ll x = powa(a, d, n);
    if(x == 1 || x == n - 1)
      return 0;
    for(int i = 0; i < s; ++i) {
      x = ((__int128) x * x) % n;
      if(x == n - 1)
        return 0;
    }
    return 1;
  }
  bool is_prime(ll x) { // use this
    if(x < 2)
      return 0;
    int r = 0;
    ll d = x - 1;
    while((d & 1) == 0) {
      d >>= 1;
      ++r;
    }
    for(auto& i : primes) {
      if(x == i)
        return 1;
      if(miller_rabin(x, i, d, r))
        return 0;
    }
    return 1;
  }
}

namespace PollardRho {
  mt19937_64 generator(chrono::steady_clock::now()
                       .time_since_epoch().count());
  uniform_int_distribution<ll> rand_ll(0, LLONG_MAX);
  ll f(ll x, ll b, ll n) { // (x^2 + b) % n
    return (((__int128) x * x) % n + b) % n;
  }
  ll rho(ll n) {
    if(n % 2 == 0)
      return 2;
    ll b = rand_ll(generator);
    ll x = rand_ll(generator);
    ll y = x;
    while(1) {
      x = f(x, b, n);
      y = f(f(y, b, n), b, n);
      ll d = MillerRabin::gcd(abs(x - y), n);
      if(d != 1)
        return d;
    }
  }
  void pollard_rho(ll n, vector<ll>& res) {
    if(n == 1)
      return;
    if(MillerRabin::is_prime(n)) {
      res.push_back(n);
      return;
    }
    ll d = rho(n);
    pollard_rho(d, res);
    pollard_rho(n / d, res);
  }
  vector<ll> factorize(ll n, bool sorted = 1) { // use this
    vector<ll> res;
    pollard_rho(n, res);
    if(sorted)
      sort(res.begin(), res.end());
    return res;
  }
}
