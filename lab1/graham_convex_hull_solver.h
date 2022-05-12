#pragma once

#include "convex_hull_solver.h"

class GrahamConvexHullSolver : public ConvexHullSolver {
   public:
    GrahamConvexHullSolver() = default;
    ~GrahamConvexHullSolver() = default;

    vector<Point> Solve(vector<Point>& points) override;
};
