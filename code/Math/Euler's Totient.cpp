// Precompute up to n in O(n log log n)
vector<int> phi_1_to_n(int n)
{
    vector<int> phi(n + 1);
    phi[0] = 0;
    phi[1] = 1;
    for(int i = 2; i <= n; i++)
        phi[i] = i;
    for(int i = 2; i <= n; i++)
        if(phi[i] == i)
            for(int j = i; j <= n; j += i)
                phi[j] -= phi[j] / i;
    return phi;
}

// Calculate for a single n in O(sqrt(n))
ll totient(ll n)
{
    ll res = 1;
    for(ll i = 2; i * i <= n; ++i)
    {
        if(n % i == 0)
        {
            res *= i - 1;
            n /= i;
        }
        while(n % i == 0)
        {
            res *= i;
            n /= i;
        }
    }
    if(n > 1) res *= n - 1;
    return res;
}
