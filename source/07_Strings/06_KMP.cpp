// Constructs KMP failure function in O(n)
vector<int> kmp(const string& s) {
  vector<int> res(s.length());
  int i = 1, j = 0;
  while(i < (int)s.length()) {
    if(s[i] == s[j])
      res[i++] = ++j;
    else if(j > 0)
      j = res[j - 1];
    else
      res[i++] = 0;
  }
  return res;
}
