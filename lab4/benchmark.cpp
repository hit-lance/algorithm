#include <benchmark/benchmark.h>



static void BM_Greedy(benchmark::State& state) {
    SetCoverSolver* s = new GreedySetCoverSolver();
    for (auto _ : state) {
        state.PauseTiming();
        auto [universe, collection] = GenerateSet(state.range(0));
        state.ResumeTiming();
        s->Solve(universe, collection);
    }
}
BENCHMARK(BM_Greedy)->Arg(100)->Arg(1000)->Arg(5000);

static void BM_ILP(benchmark::State& state) {
    SetCoverSolver* s = new ILPSetCoverSolver();
    for (auto _ : state) {
        state.PauseTiming();
        auto [universe, collection] = GenerateSet(state.range(0));
        state.ResumeTiming();
        s->Solve(universe, collection);
    }
}
BENCHMARK(BM_ILP)->Arg(100)->Arg(1000)->Arg(5000);

BENCHMARK_MAIN();
