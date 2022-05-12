#include "graham_convex_hull_solver.h"

#include <algorithm>
#include <cmath>
#include <unordered_set>

vector<Point> GrahamConvexHullSolver::Solve(vector<Point>& points) {
    if (points.size() <= 3) {
        return points;
    }

    // 1. find lowest point p0
    auto lowest_point_iter =
        min_element(points.begin(), points.end(), [](const Point& a, const Point& b) { return a.second < b.second; });
    iter_swap(points.begin(), lowest_point_iter);

    // 2. sort by angle p0 to pi
    auto consine = [](double x, double y) { return x / sqrt(pow(x, 2) + pow(y, 2)); };
    sort(next(points.begin()), points.end(), [&](const Point& a, const Point& b) {
        return consine(a.first - points[0].first, a.second - points[0].second) >
               consine(b.first - points[0].first, b.second - points[0].second);
    });

    vector<Point> convex_hull{points[0], points[1], points[2]};
    size_t n = points.size();

    // check if P is at vector AB right side
    auto is_right = [](const Point& p, const Point& a, const Point& b) {
        return (b.first - a.first) * (p.second - a.second) - (b.second - a.second) * (p.first - a.first) < 0;
    };

    for (size_t i = 3; i < n; ++i) {
        while (is_right(points[i], convex_hull[convex_hull.size() - 2], convex_hull.back())) {
            convex_hull.pop_back();
        }
        convex_hull.push_back(points[i]);
    }
    return convex_hull;
}
