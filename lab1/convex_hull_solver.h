#pragma once

#include <random>
#include <vector>

using namespace std;

using Point = pair<double, double>;

static vector<Point> GeneratePoints(size_t n) {
    vector<Point> points(n);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> unif(0, 100);
    for (size_t i = 0; i < n; ++i) {
        points[i] = {unif(rd), unif(rd)};
    }
    return points;
}

class ConvexHullSolver {
   public:
    virtual vector<Point> Solve(vector<Point>& points) = 0;

   protected:
    // check if P is at vector AB right side(i.e. A->B->P is clockwise)
    inline bool isRight(const Point& p, const Point& a, const Point& b) {
        return (b.first - a.first) * (p.second - a.second) - (b.second - a.second) * (p.first - a.first) < 0;
    };
};