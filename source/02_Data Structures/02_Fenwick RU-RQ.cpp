void updtRL(int l, int r, ll val) {
  updt(BIT1, l, val), updt(BIT1, r + 1, -val);
  updt(BIT2, l, val * (l - 1)), updt(BIT2, r + 1, -val * r);
}
ll query(int k) {
  return que(BIT1, k) * k - que(BIT2, k);
}
