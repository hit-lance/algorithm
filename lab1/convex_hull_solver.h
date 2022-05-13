#pragma once

#include <vector>

using namespace std;

using Point = pair<double, double>;

class ConvexHullSolver {
   public:
    virtual vector<Point> Solve(vector<Point>& points) = 0;

   protected:
    // check if P is at vector AB right side(i.e. A->B->P is clockwise)
    inline bool isRight(const Point& p, const Point& a, const Point& b) {
        return (b.first - a.first) * (p.second - a.second) - (b.second - a.second) * (p.first - a.first) < 0;
    };
};