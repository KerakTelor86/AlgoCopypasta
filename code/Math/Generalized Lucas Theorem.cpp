/*Special Lucas : (n,k) % p^x
  fctp[n] =  Product of the integers less than or equal 
  to n that are not divisible by p
  Precompute fctp*/
LL p
LL E(LL n,int m){
    LL tot = 0;
    while(n!=0){
        tot += n/m,n/=m;
    }
    return tot;
}
LL funct(LL n,LL base){
    LL ans = fast(fctp[base],n/base,base) * fctp[n%base] %base;
    return ans; 
}
LL F(LL n,LL base){
    LL ans = 1;
    while(n!=0){
        ans = (ans * funct(n,base))%base;
        n/=p;
    }
    return ans;
}
LL special_lucas(LL n,LL r,LL base){
    p = fprime(base); 
    LL pow = E(n,p) - E(n-r,p) - E(r,p);
    LL TOP = fast(p,pow,base) * F(n,base)%base;
    LL BOT = F(r,base) * F(n-r,base)%base;
    return (TOP * fast(BOT,totien(base) - 1,base))%base;
}
//End of Special Lucas
