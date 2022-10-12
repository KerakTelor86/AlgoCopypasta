void oddManacher(vector<int> &d1, string &s){
	int n = s.length(), l = 0, r = -1;
	d1 = vector<int>(n, 1);
	for(int i = 0 ; i < n ; ++i){
		if(i <= r){
			int idx = l + r - i;
			d1[i] = min(d1[idx], r - i + 1);
		}
		while(i + d1[i] < n && i - d1[i] >= 0 && s[i + d1[i]] == s[i - d1[i]]) ++d1[i];
		if(i + d1[i] - 1 > r){
			r = i + d1[i] - 1;
			l = i - d1[i] + 1;
		}
	}
}
void evenManacher(vector<int> &d2, string &s){
	int n = s.length(), l = 0, r = -1;
	d2 = vector<int>(n, 0);
	for(int i = 0 ; i < n ; ++i){
		if(i <= r){
			int idx = l + r - i;
			d2[i] = min(d2[idx], r - i + 1);
		}
		while(i + d2[i] < n && i - d2[i] - 1 >= 0 && s[i + d2[i]] == s[i - d2[i] - 1]) ++d2[i];
		if(i + d2[i] - 1 > r){
			r = i + d2[i] - 1;
			l = i - d2[i];
		}
	}
}