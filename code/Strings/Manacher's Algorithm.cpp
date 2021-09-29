// Computes lps array. lps[i] means the longest palindromic substring centered at i (when i is even, it is between characters. when it is odd, it is on characters)lps[0] = 0; lps[1] = 1;
REP(i,2,2*str.size()){
    int l = i/2 - lps[i]/2;
    int r = (i-1)/2 + lps[i]/2;
    while(1){ // widen
        if(l == 0 || r+1 == str.size())break;
        if(str[l-1] != str[r+1])break;
        l--, r++;
    }
    lps[i] = r - l + 1;
    // jump
    if(lps[i] > 2){
        int j = i-1, k = i+1; // while lps[j] inside lps[i]
        while(lps[j] - j < lps[i] - i) lps[k++] = lps[j--];
        lps[k] = lps[i] - (i - j); // set lps[k] to edge of lps[i]
        i = k-1; // jump to mirror, which is k
    }
}
