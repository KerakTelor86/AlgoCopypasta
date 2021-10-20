// Complexity: linear time
// Ada 2 poligon, cari poligon intersectionnya
// poly_point = hasilnya, clipper = pemotongnya
#include<bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

struct point {
  double x, y;
  point(double _x, double _y): x(_x), y(_y) {}
};
struct vec {
  double x, y;
  vec(double _x, double _y): x(_x), y(_y) {}
};

point pivot(0, 0);
vec toVec(point a, point b) {
  return vec(b.x - a.x, b.y - a.y);
}
double dist(point a, point b) {
  return hypot(a.x - b.x, a.y - b.y);
}
double cross(vec a, vec b) {
  return a.x * b.y - a.y * b.x;
}
bool ccw(point p, point q, point r) {
  return cross(toVec(p, q), toVec(p, r)) > 0;
}
bool collinear(point p, point q, point r) {
  return fabs(cross(toVec(p, q), toVec(p, r))) < EPS;
}
bool lies(point a, point b, point c) {
  if((c.x >= min(a.x, b.x) && c.x <= max(a.x, b.x)) &&
      (c.y >= min(a.y, b.y) && c.y <= max(a.y, b.y)))
    return true;
  else
    return false;
}
bool anglecmp(point a, point b) {
  if(collinear(pivot, a, b))
    return dist(pivot, a) < dist(pivot, b);
  double d1x = a.x - pivot.x, d1y = a.y - pivot.y;
  double d2x = b.x - pivot.x, d2y = b.y - pivot.y;
  return (atan2(d1y, d1x) - atan2(d2y, d2x)) < 0;
}

point intersect(point s1, point e1, point s2, point e2) {
  double x1, x2, x3, x4, y1, y2, y3, y4;
  x1 = s1.x;
  y1 = s1.y;
  x2 = e1.x;
  y2 = e1.y;
  x3 = s2.x;
  y3 = s2.y;
  x4 = e2.x;
  y4 = e2.y;
  double num1 = (x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4);
  double num2 = (x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4);
  double den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
  double new_x = num1 / den;
  double new_y = num2 / den;
  return point(new_x, new_y);
}

void clip(vector <point>& poly_points, point point1, point point2) {
  vector <point> new_points;
  new_points.clear();
  for(int i = 0; i < poly_points.size(); i++) {
    int k = (i + 1) % poly_points.size();
    double i_pos = ccw(point1, point2, poly_points[i]);
    double k_pos = ccw(point1, point2, poly_points[k]);
    //in in
    if(i_pos <= 0  && k_pos <= 0)
      new_points.push_back(poly_points[k]);
    //out in
    else if(i_pos > 0  && k_pos <= 0) {
      new_points.push_back(intersect(point1, point2, poly_points[i],
                                     poly_points[k]));
      new_points.push_back(poly_points[k]);
    }
    // in out
    else if(i_pos <= 0  && k_pos > 0) {
      new_points.push_back(intersect(point1, point2, poly_points[i],
                                     poly_points[k]));
    }
    //out out
    else {
    }
  }
  poly_points.clear();
  for(int i = 0; i < new_points.size(); i++)
    poly_points.push_back(new_points[i]);
}
double area(const vector <point>& P) {
  double result = 0.0;
  double x1, y1, x2, y2;
  for(int i = 0; i < P.size() - 1; i++) {
    x1 = P[i].x;
    y1 = P[i].y;
    x2 = P[i + 1].x;
    y2 = P[i + 1].y;
    result += (x1 * y2 - x2 * y1);
  }
  return fabs(result) / 2;
}
void suthHodgClip(vector <point>& poly_points, vector <point> clipper_points) {
  for(int i = 0; i < clipper_points.size(); i++) {
    int k = (i + 1) % clipper_points.size();
    clip(poly_points, clipper_points[i], clipper_points[k]);
  }
}
vector<point> sortku(vector<point> P) {
  int P0 = 0;
  int i;
  for(i = 1; i < 3; i++) {
    if(P[i].y < P[P0].y || (P[i].y == P[P0].y && P[i].x > P[P0].x))
      P0 = i;
  }
  point temp = P[0];
  P[0] = P[P0];
  P[P0] = temp;
  pivot = P[0];
  sort(++P.begin(), P.end(), anglecmp);
  reverse(++P.begin(), P.end());
  return P;
}
int main {
  clipper_points = sortku(clipper_points);
  suthHodgClip(poly_points, clipper_points);
}
