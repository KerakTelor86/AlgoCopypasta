typedef double TD;                // for precision shits
namespace GEOM {
typedef pair<TD, TD> Pt;        // vector and points
const TD EPS = 1e-9;
const TD maxD = 1e9;
TD cross(Pt a, Pt b, Pt c) {    // right hand rule
  TD v1 = a.first - c.first;    // (a-c) X (b-c)
  TD v2 = a.second - c.second;
  TD u1 = b.first - c.first;
  TD u2 = b.second - c.second;
  return v1 * u2 - v2 * u1;
}
TD cross(Pt a, Pt b) {          // a X b
  return a.first * b.second - a.second * b.first;
}
TD dot(Pt a, Pt b, Pt c) {      // (a-c) . (b-c)
  TD v1 = a.first - c.first;
  TD v2 = a.second - c.second;
  TD u1 = b.first - c.first;
  TD u2 = b.second - c.second;
  return v1 * u1 + v2 * u2;
}
TD dot(Pt a, Pt b) {            // a . b
  return a.first * b.first + a.second * b.second;
}
TD dist(Pt a, Pt b) {
  return sqrt((a.first - b.first) * (a.first - b.first) +
              (a.second - b.second) * (a.second - b.second));
}
TD shoelaceX2(vector<Pt>& convHull) {
  TD ret = 0;
  for(int i = 0, n = convHull.size(); i < n; i++)
    ret += cross(convHull[i], convHull[(i + 1) % n]);
  return ret;
}
vector<Pt> createConvexHull(vector<Pt>& points) {
  sort(points.begin(), points.end());
  vector<Pt> ret;
  for(int i = 0; i < points.size(); i++) {
    while(ret.size() > 1 &&
          cross(points[i], ret[ret.size() - 1], ret[ret.size() - 2]) < -EPS)
      ret.pop_back();
    ret.push_back(points[i]);
  }
  for(int i = points.size() - 2, sz = ret.size(); i >= 0; i--) {
    while(ret.size() > sz &&
          cross(points[i], ret[ret.size() - 1], ret[ret.size() - 2]) < -EPS)
      ret.pop_back();
    if(i == 0)
      break;
    ret.push_back(points[i]);
  }
  return ret;
  bool isInside(Pt pv, vector<Pt>& x) { //using winding number
    int n = x.size(), wn = 0;
    x.push_back(x[0]);
    for(int i = 0; i < n; ++i) {
      if(((x[i + 1].first <= pv.first && x[i].first >= pv.first) ||
          (x[i + 1].first >= pv.first && x[i].first <= pv.first)) &&
          ((x[i + 1].second <= pv.second && x[i].second >= pv.second) ||
           (x[i + 1].second >= pv.second && x[i].second <= pv.second))) {
        if(cross(x[i], x[i + 1], pv) == 0) {
          x.pop_back();
          return true;
        }
      }
    }
    for(int i = 0; i < n; ++i) {
      if(x[i].second <= pv.second) {
        if(x[i + 1].second > pv.second && cross(x[i], x[i + 1], pv) > 0)
          ++wn;
      } else if(x[i + 1].second <= pv.second && cross(x[i], x[i + 1], pv) < 0)
        --wn;
    }
    x.pop_back();
    return wn != 0;
  }
}
bool isInside(Pt pv, vector<Pt>& x) { //using winding number
  int n = x.size(), wn = 0;
  x.push_back(x[0]);
  for(int i = 0; i < n; ++i) {
    if(((x[i + 1].first <= pv.first && x[i].first >= pv.first) ||
        (x[i + 1].first >= pv.first && x[i].first <= pv.first)) &&
        ((x[i + 1].second <= pv.second && x[i].second >= pv.second) ||
         (x[i + 1].second >= pv.second && x[i].second <= pv.second))) {
      if(cross(x[i], x[i + 1], pv) == 0) {
        x.pop_back();
        return true;
      }
    }
  }
  for(int i = 0; i < n; ++i) {
    if(x[i].second <= pv.second) {
      if(x[i + 1].second > pv.second && cross(x[i], x[i + 1], pv) > 0)
        ++wn;
    } else if(x[i + 1].second <= pv.second && cross(x[i], x[i + 1], pv) < 0)
      --wn;
  }
  x.pop_back();
  return wn != 0;
}
}

