inline short int mobius(int k){ //dp[1] = 1, p[]=faktor prima terbesar
    ls = k/p[k];
    if(p[k]==p[ls]||!dp[ls])return dp[k] = 0;
    return dp[k] = (dp[ls]==-1) ? 1 : -1;
}

