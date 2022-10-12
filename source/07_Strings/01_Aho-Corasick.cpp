const int K = 26;
struct Vertex {
public:
	int go[K], next[K], p = -1, link = -1, exit_link;
	bool leaf = false;
	char pch;
	vector<int> idx;
 
	Vertex(int p=-1, char ch='$') : p(p), pch(ch) {
		fill(begin(next), end(next), -1);
		fill(begin(go), end(go), -1);
		exit_link = -1;
	}
};
 
class Aho {
public:
	vector<Vertex> t = vector<Vertex>(1);
	vector<vector<int>> occ;
	vector<string> pat;
	string txt;
 
	void add_string(int num, string &s) {
		int v = 0;
		for(char ch : s) {
			int c = ch - 'a';
			if(t[v].next[c] == -1) {
				t[v].next[c] = t.size();
				t.emplace_back(v, ch);
			}
			v = t[v].next[c];
		}
		t[v].leaf = true;
		t[v].idx.pb(num);
	}
 
	int get_link(int v) {
		if(t[v].link == -1) {
			if(v == 0 || t[v].p == 0) t[v].link = 0;
			else t[v].link = go(get_link(t[v].p), t[v].pch);
		}
		return t[v].link;
	}
 
	int go(int v, char ch) {
		int c = ch - 'a';
		if(t[v].go[c] == -1) {
			if(t[v].next[c] != -1) t[v].go[c] = t[v].next[c];
			else t[v].go[c] = v == 0 ? 0 : go(get_link(v), ch);
		}
		return t[v].go[c];
	}
 
	int find_exit(int v){
		if(t[v].exit_link != -1) return t[v].exit_link;
		if(v == 0) return 0;
		int nxt = get_link(v);
		if(t[nxt].idx.size()) return nxt;
		return t[v].exit_link = find_exit(nxt);
	}
 
	void add_occur(int v, int i){
		for(int &x : t[v].idx){
			occ[x].pb(i - pat[x].length() + 1);
		}
		if(v == 0) return ;
		add_occur(find_exit(v), i);
	}
};