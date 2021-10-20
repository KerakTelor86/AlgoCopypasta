void f(int rem, int l, int r, int optl, int optr) {
  if(l > r)
    return;
  int mid = l + r >> 1;
  int opt = MOD, optid = mid;
  for(int i = optl; i <= mid && i <= optr; ++i) {
    if(dp[rem - 1][i] + c[i][mid] < opt) {
      opt = dp[rem - 1][i] + c[i][mid];
      optid = i;
    }
  }
  dp[rem][mid] = opt;
  f(rem, l, mid - 1, optl, optid);
  f(rem, mid + 1, r, optid, optr);
  return;
}
rep(i, 1, n)dp[1][i] = c[0][i];
rep(i, 2, k)f(i, i, n, i, n);
