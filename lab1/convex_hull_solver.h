#pragma once

#include <vector>

using namespace std;

using Point = pair<double, double>;

class ConvexHullSolver {
   public:
    virtual vector<Point> Solve(vector<Point>& points) = 0;
};