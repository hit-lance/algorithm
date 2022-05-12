#pragma once

#include "convex_hull_solver.h"

class DivideConvexHullSolver : public ConvexHullSolver {
   public:
    DivideConvexHullSolver() = default;
    ~DivideConvexHullSolver() = default;

    vector<Point> Solve(vector<Point>& points) override;

   private:
    vector<Point> Divide(vector<Point>::iterator first, vector<Point>::iterator last);
    vector<Point> Merge(vector<Point>& left_ch, vector<Point>& right_ch);
    void Merge3(vector<Point>& result, const vector<Point>& a, const vector<Point>& b, const vector<Point>& c);
};
