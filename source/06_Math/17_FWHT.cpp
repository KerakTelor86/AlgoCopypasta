// Desc  : Transform a polynom to obtain a_i * b_j * x^(i XOR j) or combinations
// Time  : O(N log N) with N = 2^K
// OP  => c00 c01 c10 c11 | c00 c01 c10 c11 inv
// XOR =>  +1  +1  +1  -1 |  +1  +1  +1  -1 | div the inverse with size = n
// AND =>   1  +1   0   1 |   1  -1   0   1 | no comment
//  OR =>   1   0  +1   1 |   1   0  -1   1 | no comment
typedef vector<long long> vec;
void FWHT(vec& a) {
  int n = a.size();
  for(int lvl = 1; 2 * lvl <= n; lvl <<= 1) {
    for(int i = 0; i < n; i += 2 * lvl) {
      for(int j = 0; j < lvl; j++) { // do not forget to modulo
        long long u = a[i + j], v = a[i + lvl + j];
        a[i + j]       = u + v; // c00 * u + c01 * v
        a[i + lvl + j] = u - v; // c10 * u + c11 * v
      }
    }
  }
}  // you can convolve as usual
