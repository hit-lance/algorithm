#pragma once

#include <random>
#include <unordered_set>
#include <vector>

using namespace std;

using Point = pair<double, double>;

static vector<Point> GeneratePoints(size_t n) {
    vector<Point> points(n);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> unif(0, 100);
    for (size_t i = 0; i < n; ++i) {
        points[i] = {unif(rd), unif(rd)};
    }
    return points;
}

class SetCoverSolver {
   public:
    virtual vector<unordered_set<int>> Solve(unordered_set<int> universe, vector<unordered_set<int>> collection) = 0;
};