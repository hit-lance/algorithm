#pragma once

#include "convex_hull_solver.h"

class EnumerateConvexHullSolver : public ConvexHullSolver {
   public:
    EnumerateConvexHullSolver() = default;
    ~EnumerateConvexHullSolver() = default;

    vector<Point> Solve(vector<Point>& points) override;

   private:
    bool CheckPointInTriangle(const Point& p, const Point& a, const Point& b, const Point& c) const;
};
