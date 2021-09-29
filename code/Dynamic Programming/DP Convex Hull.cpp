/* dp[i] = min k<i {dp[k] + x[i]*m[k]}
   Make sure gradient (m[i]) is either non-increasing if min,
   or non-decreasing if max. x[i] must be non-decreasing. just sort */
int y[N], m[N];
// while this is true, pop back from dq. a=new line, b=last, c=2nd last
bool cekx(int a, int b, int c){
    // if not enough, change to cross mul
    // if cross mul, beware of negative denominator, and overflow
    return (double)(y[b]-y[a])/(m[a]-m[b])<=(double)(y[c]-y[b])/(m[b]-m[c]); 
}
