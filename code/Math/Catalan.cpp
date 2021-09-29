long long cat(long long n){
    long long ret = 1;
    for(long long i = 0; i < n; i++){
        ret = ret*(2*n-i);
        ret = ret/(i+1);
    }
    ret = ret/(n+1);
    return ret;
}

ll superCatalan(int n){  
    if(n <= 2)return 1;  
    return (3*(2*n-3)*sc(n-1)-(n-3)*sc(n-2)) / n; 
} // 1,1,1,3,11,45, 197, 903, 4279, 20793, 103049 
