int build_cen(int nw) {
  com_cen(nw, 0); //fungsi untuk itung size subtree
  int siz = sz[nw] / 2;
  bool found = false;
  while(!found) {
    found = true;
    for(int i : v[nw]) {
      if(!rem[i] && sz[i] < sz[nw]) {
        if(sz[i] > siz) {
          found = false;
          nw = i;
          break;
        }
      }
    }
  }
  big
  rem[nw] = true;
  for(int i : v[nw])if(!rem[i])
      par_cen[build_cen(i)] = nw;
  return nw;
}
