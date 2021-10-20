
typedef long long int TD;
const TD INF = 10000000000000;
namespace LICHAO {
struct Node {
  TD m, c;
  Node* l, *r;
};
Node* newNode(Node* x = NULL) {
  Node* ret = (Node*)malloc(sizeof(Node));
  if(x)
    ret->m = x->m, ret->c = x->c;
  ret->l = ret->r = NULL;
  return ret;
}
void update(Node* k, TD l, TD r, TD m, TD c) {
  TD mid = l + r >> 1;
  bool le = m * l + c < k->m * l + k->c;
  bool ri = m * mid + c < k->m * mid + k->c;
  if(ri)
    swap(k->m, m), swap(k->c, c);
  if(r - l <= 1)
    return;
  else if(le != ri)
    update((k->l) ? (k->l) : (k->l = newNode(k)), l, mid, m, c);
  else
    update((k->r) ? (k->r) : (k->r = newNode(k)), mid, r, m, c);
}
TD query(Node* k, TD l, TD r, TD p) {
  if(!k)
    return INF;
  if(r - l <= 1)
    return p * k->m + k->c;
  if(p < (l + r >> 1))
    return min(p * k->m + k->c, query(k->l, l, l + r >> 1, p));
  else
    return min(p * k->m + k->c, query(k->r, l + r >> 1, r, p));
}
}
