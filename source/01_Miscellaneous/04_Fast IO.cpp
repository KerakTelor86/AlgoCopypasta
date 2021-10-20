int read() {
  char c;
  do {
    c = getchar_unlocked();
  } while(c < 33);
  int res = 0;
  int mul = 1;
  if(c == '-') {
    mul = -1;
    c = getchar_unlocked();
  }
  while('0' <= c && c <= '9') {
    res = res * 10 + c - '0';
    c = getchar_unlocked();
  }
  return res * mul;
}

void write(int x) {
  static char wbuf[10];
  if(x < 0) {
    putchar_unlocked('-');
    x = -x;
  }
  int idx = 0;
  while(x) {
    wbuf[idx++] = x % 10;
    x /= 10;
  }
  if(idx == 0)
    putchar_unlocked('0');
  for(int i = idx - 1; i >= 0; --i)
    putchar_unlocked(wbuf[i] + '0');
}

void write(const char* s) {
  while(*s) {
    putchar_unlocked(*s);
    ++s;
  }
}
