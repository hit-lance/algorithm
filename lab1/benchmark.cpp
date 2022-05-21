#include <benchmark/benchmark.h>

#include <algorithm>
#include <iostream>
#include <random>

#include "divide_convex_hull_solver.h"
#include "enumerate_convex_hull_solver.h"
#include "graham_convex_hull_solver.h"

static void BM_EnumerateConvexHull(benchmark::State& state) {
    ConvexHullSolver* s = new EnumerateConvexHullSolver();
    for (auto _ : state) {
        state.PauseTiming();
        vector<Point> points = GeneratePoints(state.range(0));
        state.ResumeTiming();
        s->Solve(points);
    }
}
BENCHMARK(BM_EnumerateConvexHull)->DenseRange(10, 100, 10);

static void BM_GrahamConvexHullSolver(benchmark::State& state) {
    ConvexHullSolver* s = new GrahamConvexHullSolver();
    for (auto _ : state) {
        state.PauseTiming();
        vector<Point> points = GeneratePoints(state.range(0));
        state.ResumeTiming();
        s->Solve(points);
    }
}
BENCHMARK(BM_GrahamConvexHullSolver)->DenseRange(10, 100, 10);

static void BM_DivideConvexHullSolver(benchmark::State& state) {
    ConvexHullSolver* s = new DivideConvexHullSolver();
    for (auto _ : state) {
        state.PauseTiming();
        vector<Point> points = GeneratePoints(state.range(0));
        state.ResumeTiming();
        s->Solve(points);
    }
}
BENCHMARK(BM_DivideConvexHullSolver)->DenseRange(10, 100, 10);

BENCHMARK_MAIN();
