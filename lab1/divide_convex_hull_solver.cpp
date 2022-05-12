#include "divide_convex_hull_solver.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <numeric>
#include <unordered_set>

vector<Point> DivideConvexHullSolver::Solve(vector<Point>& points) {
    if (points.size() <= 3) {
        return points;
    }

    return Divide(points.begin(), points.end());
}

vector<Point> DivideConvexHullSolver::Divide(vector<Point>::iterator left, vector<Point>::iterator right) {
    cout << right - left << endl;
    if (right - left < 3) {
        return vector<Point>(left, right);
    }

    if (right - left == 3) {
        // check if A->B->C is clockwise(i.e. C is at right side of vector AB).
        auto is_clockwise = [](const Point& a, const Point& b, const Point& c) {
            return (b.first - a.first) * (c.second - a.second) - (b.second - a.second) * (c.first - a.first) < 0;
        };
        vector<Point> ch(left, right);
        if (is_clockwise(ch[0], ch[1], ch[2])) {
            swap(ch[0], ch[1]);
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
    vector<Point> ch;
    auto p =
        min_element(left_ch.begin(), left_ch.end(), [](const Point& a, const Point& b) { return a.first < b.first; });
    ch.push_back(*p);

    left_ch.erase(p);

    auto sine = [](double x, double y) { return y / sqrt(pow(x, 2) + pow(y, 2)); };
    auto cmp = [&](const Point& a, const Point& b) {
        return sine(a.first - p->first, a.second - p->second) > sine(b.first - p->first, b.second - p->second);
    };
    auto u = min_element(right_ch.begin(), right_ch.end(), cmp);
    auto v = max_element(right_ch.begin(), right_ch.end(), cmp);

    assert(left_ch.size() > 0 && right_ch.size() > 1 && u != v);

    vector<Point> right_ch_1;
    auto it = v;
    for (; it != u; ++it) {
        if (it == right_ch.end()) {
            it = right_ch.begin();
        }
        right_ch_1.push_back(*it);
    }

    assert(it != v);

    vector<Point> right_ch_2(right_ch.size() - right_ch_1.size());
    for (size_t i = right_ch_2.size() - 1; it != v; ++it) {
        if (it == right_ch.end()) {
            it = right_ch.begin();
        }
        right_ch_1[i--] = *it;
    }

    assert(right_ch_1.size() > 0 && right_ch_2.size() > 0);

    Merge3(ch, left_ch, right_ch_1, right_ch_2);
    return ch;
}

void DivideConvexHullSolver::Merge3(vector<Point>& result, const vector<Point>& a, const vector<Point>& b,
                                    const vector<Point>& c) {
    size_t m = a.size(), n = b.size(), o = c.size(), i = 0, j = 0, k = 0;
    result.reserve(1 + m + n + o);

    while (i < m && j < n && k < o) {
        if (a[i] <= b[j] && a[i] <= c[k]) {
            result.push_back(a[i++]);
        } else if (b[j] <= c[k]) {
            result.push_back(b[j++]);
        } else {
            result.push_back(c[k++]);
        }
    }

    while (i < m && j < n) {
        if (a[i] <= b[j]) {
            result.push_back(a[i++]);
        } else {
            result.push_back(b[j++]);
        }
    }

    while (i < m && k < o) {
        if (a[i] <= c[k]) {
            result.push_back(a[i++]);
        } else {
            result.push_back(c[k++]);
        }
    }

    while (j < n && k < o) {
        if (b[j] <= c[k]) {
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