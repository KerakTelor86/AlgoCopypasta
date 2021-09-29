/*
   Eertree - keep track of all palindromes and its occurences
   This code refers to problem Longest Palindromic Substring
https://www.spoj.com/problems/LPS/
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct node {
    int next[26];
    int sufflink;
    int len, cnt;
};

const int N = 1e5+69;
int n;
string s;
node tree[N];
int idx, suff;
int ans = 0;

void init_eertree() {
    idx = suff = 2;
    tree[1].len = -1, tree[1].sufflink = 1;
    tree[2].len = 0, tree[2].sufflink = 1;
}

bool add_letter(int x) {
    int cur = suff, curlen = 0;
    int nw = s[x] - 'a';

    while(1) {
        curlen = tree[cur].len;
        if(x-curlen-1 >= 0 && s[x-curlen-1] == s[x])
            break;
        cur = tree[cur].sufflink;
    }

    if(tree[cur].next[nw]) {
        suff = tree[cur].next[nw];
        return 0;
    }


    tree[cur].next[nw] = suff = ++idx;
    tree[idx].len = tree[cur].len + 2;
    ans = max(ans, tree[idx].len);

    if(tree[idx].len == 1) {
        tree[idx].sufflink = 2;
        tree[idx].cnt = 1;
        return 1;
    }

    while(1) {
        cur = tree[cur].sufflink;
        curlen = tree[cur].len;
        if(x-curlen-1 >= 0 && s[x-curlen-1] == s[x]) {
            tree[idx].sufflink = tree[cur].next[nw];
            break;
        }
    }
    tree[idx].cnt = tree[tree[idx].sufflink].cnt + 1;

    return 1;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> s;
    init_eertree();
    for(int i = 0; i < n; i++) {
        add_letter(i);
    }
    cout << ans << '\n';
    return 0;
}
