#include "divide_convex_hull_solver.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <numeric>
#include <unordered_set>

vector<Point> DivideConvexHullSolver::Solve(vector<Point>& points) { return Divide(points.begin(), points.end()); }

vector<Point> DivideConvexHullSolver::Divide(vector<Point>::iterator left, vector<Point>::iterator right) {
    if (right - left < 3) {
        return vector<Point>(left, right);
    }

    if (right - left == 3) {
        vector<Point> ch(left, right);
        if (isRight(ch[0], ch[1], ch[2])) {
            swap(ch[1], ch[2]);
        }
        auto p = min_element(ch.begin(), ch.end(), [](const Point& a, const Point& b) { return a.first < b.first; });
        if (p != ch.begin()) {
            swap(*p, ch[0]);
            swap(ch[1], ch[2]);
        }
        return ch;
    }

    auto m = left + (right - left) / 2;
    std::nth_element(left, m, right, [](const Point& a, const Point& b) { return a.first < b.first; });

    vector<Point> left_ch = Divide(left, m);
    vector<Point> right_ch = Divide(m, right);

    return Merge(left_ch, right_ch);
}

vector<Point> DivideConvexHullSolver::Merge(vector<Point>& left_ch, vector<Point>& right_ch) {
    vector<Point> points;
    auto p =
        min_element(left_ch.begin(), left_ch.end(), [](const Point& a, const Point& b) { return a.first < b.first; });
    points.push_back(*p);

    left_ch.erase(p);

    auto u = max_element(right_ch.begin(), right_ch.end(),
                         [&](const Point& a, const Point& b) { return isRight(a, points[0], b); });
    auto v = min_element(right_ch.begin(), right_ch.end(),
                         [&](const Point& a, const Point& b) { return isRight(a, points[0], b); });

    assert(left_ch.size() > 0 && right_ch.size() > 1 && u != v);

    vector<Point> right_ch_1;
    auto it = v;
    while (it != u) {
        if (it == right_ch.end()) {
            it = right_ch.begin();
            continue;
        }
        right_ch_1.push_back(*it++);
    }

    assert(it != v);

    vector<Point> right_ch_2(right_ch.size() - right_ch_1.size());
    size_t i = right_ch_2.size() - 1;
    while (it != v) {
        if (it == right_ch.end()) {
            it = right_ch.begin();
            continue;
        }
        right_ch_2[i--] = *it++;
    }

    assert(right_ch_1.size() > 0 && right_ch_2.size() > 0);

    Merge3(points, left_ch, right_ch_1, right_ch_2);

    vector<Point> convex_hull{points[0], points[1], points[2]};
    size_t n = points.size();

    for (size_t i = 3; i < n; ++i) {
        while (isRight(points[i], convex_hull[convex_hull.size() - 2], convex_hull.back())) {
            convex_hull.pop_back();
        }
        convex_hull.push_back(points[i]);
    }
    return convex_hull;
}

void DivideConvexHullSolver::Merge3(vector<Point>& result, const vector<Point>& a, const vector<Point>& b,
                                    const vector<Point>& c) {
    size_t m = a.size(), n = b.size(), o = c.size(), i = 0, j = 0, k = 0;
    result.reserve(1 + m + n + o);

    while (i < m && j < n && k < o) {
        if (isRight(a[i], result[0], b[j]) && isRight(a[i], result[0], c[k])) {
            result.push_back(a[i++]);
        } else if (isRight(b[j], result[0], c[k])) {
            result.push_back(b[j++]);
        } else {
            result.push_back(c[k++]);
        }
    }

    while (i < m && j < n) {
        if (isRight(a[i], result[0], b[j])) {
            result.push_back(a[i++]);
        } else {
            result.push_back(b[j++]);
        }
    }

    while (i < m && k < o) {
        if (isRight(a[i], result[0], c[k])) {
            result.push_back(a[i++]);
        } else {
            result.push_back(c[k++]);
        }
    }

    while (j < n && k < o) {
        if (isRight(b[j], result[0], c[k])) {
            result.push_back(b[j++]);
        } else {
            result.push_back(c[k++]);
        }
    }

    while (i < m) {
        result.push_back(a[i++]);
    }
    while (j < n) {
        result.push_back(b[j++]);
    }
    while (k < o) {
        result.push_back(c[k++]);
    }
}