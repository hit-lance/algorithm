#include <benchmark/benchmark.h>

#include "greedy_set_cover_solver.h"
#include "ilp_set_cover_solver.h"

static void BM_Greedy(benchmark::State& state) {
    SetCoverSolver* s = new GreedySetCoverSolver();
    for (auto _ : state) {
        state.PauseTiming();
        auto [universe, collection] = GenerateSet(state.range(0));
        state.ResumeTiming();
        s->Solve(universe, collection);
    }
}
BENCHMARK(BM_Greedy)->Arg(8)->Arg(64)->Arg(512);

static void BM_ILP(benchmark::State& state) {
    SetCoverSolver* s = new ILPSetCoverSolver();
    for (auto _ : state) {
        state.PauseTiming();
        auto [universe, collection] = GenerateSet(state.range(0));
        state.ResumeTiming();
        s->Solve(universe, collection);
    }
}
BENCHMARK(BM_ILP)->Arg(8)->Arg(64)->Arg(512);

BENCHMARK_MAIN();
