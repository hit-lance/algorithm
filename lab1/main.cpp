#include <algorithm>
#include <iostream>
#include <random>

#include "divide_convex_hull_solver.h"
#include "enumerate_convex_hull_solver.h"
#include "graham_convex_hull_solver.h"

vector<Point> GeneratePoints(size_t n) {
    vector<Point> points(n);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> unif(0, 100);
    for (size_t i = 0; i < n; ++i) {
        points[i] = {unif(rd), unif(rd)};
    }
    return points;
}

int main() {
    vector<Point> points = GeneratePoints(1000);

    ConvexHullSolver* s1 = new EnumerateConvexHullSolver();
    ConvexHullSolver* s2 = new GrahamConvexHullSolver();
    ConvexHullSolver* s3 = new DivideConvexHullSolver();

    vector<Point> ch1 = s1->Solve(points);
    vector<Point> ch2 = s2->Solve(points);
    vector<Point> ch3 = s3->Solve(points);

    sort(ch1.begin(), ch1.end());
    sort(ch2.begin(), ch2.end());
    sort(ch3.begin(), ch3.end());

    cout << (ch2 == ch1) << " " << (ch2 == ch3) << " " << (ch1 == ch3) << endl;

    return 0;
}