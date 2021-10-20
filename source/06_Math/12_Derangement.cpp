der[0] = 1;
der[1] = 0;
for(int i = 2; i <= 10; ++i)
  der[i] = (ll)(i - 1) * (der[i - 1] + der[i - 2]);
