struct tNode{
	int key, prior;
	tNode *l, *r;
	int sz;
	tNode() {}
	tNode(int key) : key(key), prior(rand()), l(NULL), r(NULL), sz(1) {}
};
typedef tNode* pNode;

int cnt(pNode t) {
	return t ? t->sz : 0;
}
void upd(pNode t) {
	if(t) t->sz = 1 + cnt(t->l) + cnt(t->r);
}
void split(pNode t, int key, pNode &l, pNode &r){
	if(!t) l = r = NULL;
	else if(t->key <= key) {
		split(t->r, key, t->r, r);
		l = t;
	} else{
		split(t->l, key, l, t->l);
		r = t;
	}
	upd(t);
}
void ins(pNode &t, pNode it) {
	if(!t) t = it;
	else if(it->prior > t->prior) {
		split(t, it->key, it->l, it->r);
		t = it;
	} else {
		ins(t->key <= it->key ? t->r : t->l, it);
	}
	upd(t);
}
void merge(pNode &t, pNode l, pNode r) {
	if(!l || !r) t = l ? l : r;
	else if(l->prior > r->prior) {
		merge(l->r, l->r, r);
		t = l;
	} else {
		merge(r->l, l, r->l);
		t = r;
	}
	upd(t);
}
void erase(pNode &t, int key) {
	if(t->key == key) {
		pNode th = t;
		merge(t, t->l, t->r);
		delete th;
	} else {
		erase(key < t->key ? t->l : t->r, key);
	}
	upd(t);
}
pNode unite(pNode l, pNode r) {
	if(!l || !r) return l ? l : r;
	if(l->prior < r->prior) swap(l, r);
	pNode lt, rt;
	split(r, l->key, lt, rt);
	l->l = unite(l->l, lt);
	l->r = unite(l->r, rt);
	return l;
}