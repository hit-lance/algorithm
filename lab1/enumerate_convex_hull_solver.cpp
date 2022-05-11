#include "enumerate_convex_hull_solver.h"

#include <unordered_set>

vector<Point> EnumerateConvexHullSolver::Solve(vector<Point>& points) {
    unordered_set<size_t> indexes;

    size_t n = points.size();

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i; j < n; ++j) {
            for (size_t k = j; k < n; ++k) {
                for (size_t l = k; l < n; ++l) {
                    size_t counters[4] = {i, j, k, l};
                    for (int m = 0; m < 4; ++m) {
                        if (indexes.find(m) == indexes.end()) {
                            Point& p = points[counters[m]];
                            Point& a = points[counters[(m + 1) % 4]];
                            Point& b = points[counters[(m + 2) % 4]];
                            Point& c = points[counters[(m + 3) % 4]];
                            if (CheckPointInTriangle(p, a, b, c)) {
                                indexes.insert(m);
                            }
                        }
                    }
                }
            }
        }
    }

    vector<Point> convex_hull;
    for (size_t i = 0; i < n; ++i) {
        if (indexes.find(i) == indexes.end()) {
            convex_hull.emplace_back(points[i]);
        }
    }
    return convex_hull;
}

bool EnumerateConvexHullSolver::CheckPointInTriangle(const Point& p, const Point& a, const Point& b,
                                                     const Point& c) const {
    Point ap{p.first - a.first, p.second - a.second};
    Point ab{b.first - a.first, b.second - a.second};
    Point ac{c.first - a.first, c.second - a.second};

    double u = (ap.first * ac.second - ac.first * ap.second) / (ab.first * ac.second - ac.first * ab.second);
    double v = (ap.first * ab.second - ab.first * ap.second) / (ac.first * ab.second - ab.first * ac.second);
    return u > 0 && v > 0 && u + v < 1;
}