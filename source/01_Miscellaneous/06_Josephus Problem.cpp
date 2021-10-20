ll josephus(ll n, ll k) { // O(k log n)
  if(n == 1)
    return 0;
  if(k == 1)
    return n - 1;
  if(k > n)
    return (josephus(n - 1, k) + k) % n;
  ll cnt = n / k;
  ll res = josephus(n - cnt, k);
  res -= n % k;
  if(res < 0)
    res += n;
  else
    res += res / (k - 1);
  return res;
}

int josephus(int n, int k) { // O(n)
  int res = 0;
  for(int i = 1; i <= n; ++i)
    res = (res + k) % i;
  return res + 1;
}
