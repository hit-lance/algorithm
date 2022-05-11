#include <iostream>

#include "enumerate_convex_hull_solver.h"

int main() {
    vector<Point> points{{1, 1}, {2, 2}, {2, 0}, {2, 4}, {3, 3}, {4, 2}};
    ConvexHullSolver* enumerate_solver = new EnumerateConvexHullSolver();

    vector<Point> convex_hull = enumerate_solver->Solve(points);
    for (auto& p : convex_hull) {
        cout << p.first << " " << p.second << endl;
    }
    return 0;
}