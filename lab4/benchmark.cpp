#include <benchmark/benchmark.h>

#include "quicksort.h"

static void BM_MyQuickSort(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        auto nums = GenerateNums(state.range(0));
        state.ResumeTiming();
        QuickSort(nums, 0, nums.size() - 1);
    }
}
BENCHMARK(BM_MyQuickSort)->DenseRange(0, 100, 10);

static void BM_STLSort(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        auto nums = GenerateNums(state.range(0));
        state.ResumeTiming();
        sort(nums.begin(), nums.end());
    }
}
BENCHMARK(BM_STLSort)->DenseRange(0, 100, 10);

BENCHMARK_MAIN();
