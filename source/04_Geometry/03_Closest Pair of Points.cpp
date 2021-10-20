#define fi first
#define se second
typedef pair<int, int> pii;
struct Point {
  int x, y, id;
};
int compareX(const void* a, const void* b) {
  Point* p1 = (Point*)a, *p2 = (Point*)b;
  return (p1->x - p2->x);
}
int compareY(const void* a, const void* b) {
  Point* p1 = (Point*)a, *p2 = (Point*)b;
  return (p1->y - p2->y);
}
double dist(Point p1, Point p2) {
  return sqrt((double)(p1.x - p2.x) * (p1.x - p2.x) +
              (double)(p1.y - p2.y) * (p1.y - p2.y)
             );
}
pair<pii, double> bruteForce(Point P[], int n) {
  double min = 1e8;
  pii ret = pii(-1, -1);
  for(int i = 0; i < n; ++i)
    for(int j = i + 1; j < n; ++j)
      if(dist(P[i], P[j]) < min) {
        ret = pii(P[i].id, P[j].id);
        min = dist(P[i], P[j]);
      }
  return pair<pii, double> (ret, min);
}
pair<pii, double> getmin(pair<pii, double> x, pair<pii, double> y) {
  if(x.fi.fi == -1 && x.fi.se == -1)
    return y;
  if(y.fi.fi == -1 && y.fi.se == -1)
    return x;
  return (x.se < y.se) ? x : y;
}
pair<pii, double> stripClosest(Point strip[], int size, double d) {
  double min = d;
  pii ret = pii(-1, -1);
  qsort(strip, size, sizeof(Point), compareY);
  for(int i = 0; i < size; ++i)
    for(int j = i + 1; j < size && (strip[j].y - strip[i].y) < min; ++j)
      if(dist(strip[i], strip[j]) < min) {
        ret = pii(strip[i].id, strip[j].id);
        min = dist(strip[i], strip[j]);
      }
  return pair<pii, double>(ret, min);
}
pair<pii, double> closestUtil(Point P[], int n) {
  if(n <= 3)
    return bruteForce(P, n);
  int mid = n / 2;
  Point midPoint = P[mid];
  pair<pii, double> dl = closestUtil(P, mid);
  pair<pii, double> dr = closestUtil(P + mid, n - mid);
  pair<pii, double> d = getmin(dl, dr);
  Point strip[n];
  int j = 0;
  for(int i = 0; i < n; i++)
    if(abs(P[i].x - midPoint.x) < d.second)
      strip[j] = P[i], j++;
  return getmin(d, stripClosest(strip, j, d.second));
}
pair<pii, double> closest(Point P[], int n) {
  qsort(P, n, sizeof(Point), compareX);
  return closestUtil(P, n);
}
Point P[50005];
int main() {
  int n;
  scanf("%d", &n);
  for(int a = 0; a < n; a++) {
    scanf("%d%d", &P[a].x, &P[a].y);
    P[a].id = a;
  }
  pair<pii, double> hasil = closest(P, n);
  if(hasil.fi.fi > hasil.fi.se)
    swap(hasil.fi.fi, hasil.fi.se);
  printf("%d %d %.6lf\n", hasil.fi.fi, hasil.fi.se, hasil.se);
  return 0;
}
