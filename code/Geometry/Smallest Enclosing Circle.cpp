// Welzl's algorithm to find the smallest circle
// that encloses a group of poins in O(N * ITERS)
// returns {radius, x, y}
const int ITERS = 3e5;
const double INF = 1e12;

tuple<double, double, double> welzl(const vector<pair<int, int>>& points)
{
    double xt = 0, yt = 0;
    for(auto& [x, y] : points)
    {
        xt += x;
        yt += y;
    }
    xt /= points.size();
    yt /= points.size();
    double p = 0.1;
    double mx_d;
    for(int i = 0; i < ITERS; ++i)
    {
        mx_d = -INF;
        int mx_idx = -1;
        for(int j = 0; j < (int) points.size(); ++j)
        {
            double cx = xt - points[j].first;
            double cy = yt - points[j].second;
            double cur = cx * cx + cy * cy;
            if(cur > mx_d)
            {
                mx_d = cur;
                mx_idx = j;
            }
        }
        xt += (points[mx_idx].first - xt) * p;
        yt += (points[mx_idx].second - yt) * p;
        p *= 0.999;
    }
    return {sqrt(mx_d), xt, yt};
}
