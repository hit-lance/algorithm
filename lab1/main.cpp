#include <benchmark/benchmark.h>

#include <algorithm>
#include <iostream>
#include <random>

#include "divide_convex_hull_solver.h"
#include "enumerate_convex_hull_solver.h"
#include "graham_convex_hull_solver.h"

#define N 500

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

static void BM_EnumerateConvexHull(benchmark::State& state) {
    ConvexHullSolver* s = new EnumerateConvexHullSolver();
    for (auto _ : state) {
        vector<Point> points = GeneratePoints(N);
        s->Solve(points);
    }
}
BENCHMARK(BM_EnumerateConvexHull);

static void BM_GrahamConvexHullSolver(benchmark::State& state) {
    ConvexHullSolver* s = new GrahamConvexHullSolver();
    for (auto _ : state) {
        vector<Point> points = GeneratePoints(N);
        s->Solve(points);
    }
}
BENCHMARK(BM_GrahamConvexHullSolver);

static void BM_DivideConvexHullSolver(benchmark::State& state) {
    ConvexHullSolver* s = new DivideConvexHullSolver();
    for (auto _ : state) {
        vector<Point> points = GeneratePoints(N);
        s->Solve(points);
    }
}
BENCHMARK(BM_DivideConvexHullSolver);

BENCHMARK_MAIN();
