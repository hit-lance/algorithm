#include <gtest/gtest.h>

#include <algorithm>
#include <iostream>
#include <random>

#include "divide_convex_hull_solver.h"
#include "enumerate_convex_hull_solver.h"
#include "graham_convex_hull_solver.h"

#define N 10

// Demonstrate some basic assertions.
TEST(ConvexHullTest, BasicAssertions) {
    for (size_t i = 0; i < N; ++i) {
        vector<Point> points = GeneratePoints(100);

        ConvexHullSolver* s1 = new EnumerateConvexHullSolver();
        ConvexHullSolver* s2 = new GrahamConvexHullSolver();
        ConvexHullSolver* s3 = new DivideConvexHullSolver();

        vector<Point> ch1 = s1->Solve(points);
        vector<Point> ch2 = s2->Solve(points);
        vector<Point> ch3 = s3->Solve(points);

        sort(ch1.begin(), ch1.end());
        sort(ch2.begin(), ch2.end());
        sort(ch3.begin(), ch3.end());

        EXPECT_EQ(ch1, ch2);
        EXPECT_EQ(ch1, ch3);
    }
}