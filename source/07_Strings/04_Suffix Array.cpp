const int VAL = 200005; // max(MXVAL, SZ)
const int SZ = 200005; // s.length()
const int LG = 20;

vector<int> pos[SZ], c[LG], p, pn;
map<int, int> nv;
int n, s[SZ], a[SZ];

int cnt[VAL];

vector<int> bldSA() {
  for(int i = 0 ; i < LG ; ++i) c[i] = vector<int>(n<<2, 0);
	pn = vector<int>(n<<2, 0); p = vector<int>(n<<2, 0);

	for(int i = 0 ; i < n ; ++i) c[0][i] = s[i];
	for(int x = 1, add = 1 ; add < n ; add <<= 1, x += 1) {
		memset(cnt, 0, sizeof(cnt));
		for(int i = 0 ; i < n ; ++i) ++cnt[c[x - 1][i + add]];
		for(int i = 1 ; i < VAL ; ++i) cnt[i] += cnt[i - 1];
		for(int i = n - 1 ; i >= 0 ; --i) p[--cnt[c[x - 1][i + add]]] = i;

		memset(cnt, 0, sizeof(cnt));
		for(int i = 0 ; i < n ; ++i) ++cnt[c[x - 1][i]];
		for(int i = 1 ; i < VAL ; ++i) cnt[i] += cnt[i - 1];
		for(int i = n - 1 ; i >= 0 ; --i) pn[--cnt[c[x - 1][p[i]]]] = p[i];

		c[x][pn[0]] = 1;
		for(int i = 1 ; i < n ; ++i) {
			c[x][pn[i]] = c[x][pn[i - 1]] + (c[x - 1][pn[i]] != c[x - 1][pn[i - 1]] || 
						  c[x - 1][pn[i] + add] != c[x - 1][pn[i - 1] + add]);
		}
	}

	return pn;
}

vector<int> kasai(string &txt, vector<int> &sa) {
	int n = txt.size();
	vector<int> lcp(n, 0), invSuff(n, 0);
	for (int i=0; i < n; i++)
		invSuff[sa[i]] = i;
	int k = 0;
	for (int i = 0; i < n; i++) {
		if (invSuff[i] == n-1){
			k = 0; continue;
		}
		int j = sa[invSuff[i]+1];
		while (i + k < n && j + k < n && txt[i + k] == txt[j + k])
			k++;
		lcp[invSuff[i]] = k;
		if (k > 0) k--;
	}
	return lcp;
}

bool check(int i, int j) {
	int len = j - i;
  for(int x = LG - 1 ; x >= 0 ; --x) {
		if(len < (1<<x)) continue;
		if(c[x][i] == c[x][j]) {
			i += (1<<x); j += (1<<x);
			len -= (1<<x);
		}
	}

	return !len;
}
