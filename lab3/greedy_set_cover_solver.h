#pragma once

#include "set_cover_solver.h"

class GreedySetCoverSolver : public SetCoverSolver {
   public:
    GreedySetCoverSolver() = default;
    ~GreedySetCoverSolver() = default;

    vector<unordered_set<int>> Solve(unordered_set<int> universe, vector<unordered_set<int>> collection) override;
};
