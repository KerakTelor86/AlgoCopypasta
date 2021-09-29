struct node{
    node* next[256],* fail,* suflink;
    int id;
    node() : fail(NULL), suflink(NULL), id(-1){
        for (int i = 0; i < 256; i++) next[i] = NULL; }
} head;

vector<string>pats; // stores unique strings
vector<int>patIdx; // stores index of string in pats
vector<vector<int> >match; // stores all matched pats in str

void addPat(string pat){ // returns string id
    node* now = &head;
    for (int i = 0; i < pat.size(); i++) {
        if(!now->next[pat[i]])now->next[pat[i]] = new node();
        now = now->next[pat[i]];
    }
    if(now->id == -1){ // prevents doubles
        now->id = pats.size();
        pats.pb(pat);
        match.pb(vector<int>());
    }
    patIdx.pb(now->id);
}
queue<node*>q;
void buildAutomaton(){
    q.push(&head);
    while(!q.empty()){
        node* now = q.front();
        q.pop();
        for (int i = 0; i < 256; i++) {
            if(!now->next[i])continue;
            node* nt = now->next[i];
            nt->fail = now->fail;
            while(nt->fail && !nt->fail->next[i])nt->fail = nt->fail->fail;
            if(nt->fail)nt->fail = nt->fail->next[i];
            else nt->fail = &head;
            if(nt->fail->id != -1)nt->suflink = nt->fail;
            else nt->suflink = nt->fail->suflink;
            q.push(nt);
        }}}
void searchStr(string str){
    node* now = &head;
    for (int i = 0; i < str.size(); i++) {
        while(now != &head && !now->next[str[i]])now = now->fail;
        if(now->next[str[i]]){
            now = now->next[str[i]];
            for(node* curr = now; curr; curr = curr->suflink){ // iterate links
                if(curr->id == -1)continue;
                match[curr->id].pb(i - pats[curr->id].size() + 1);
            }}}}
int main() {
    // clear for multiple testcase
    pats.clear(); patIdx.clear();
    head = node();
    while (!q.empty()) q.pop();

    foreach pattern: addPat(p);
    buildAutomaton();

    // clear match before every searchStr
    for (int i = 0; i < match.size(); i++) match[i].clear();
    searchStr(s);
    match[patIdx[i]] stores all patterns found in s,
        i.e. all index of s where pattern_i is found
}
