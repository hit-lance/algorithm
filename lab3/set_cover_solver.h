#pragma once

#include <random>
#include <unordered_set>
#include <vector>

using namespace std;

using Point = pair<double, double>;

static pair<unordered_set<int>, vector<unordered_set<int>>> GenerateSet(size_t size) {
    unordered_set<int> universe;
    vector<unordered_set<int>> collection(size);
    for (int i = 0; i < size; ++i) {
        universe.insert(i);
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> unif1(0, size - 1), unif2(1, 3);

    for (size_t i = 0; i < size; ++i) {
        int n = unif2(rd);
        for (size_t j = 0; j < n; ++j) {
            collection[i].insert(unif1(rd));
        }
        collection[unif1(rd)].insert(i);
    }

    return {universe, collection};
}

class SetCoverSolver {
   public:
    virtual vector<unordered_set<int>> Solve(unordered_set<int> universe, vector<unordered_set<int>> collection) = 0;
};