#pragma once

#include "set_cover_solver.h"

class ILPSetCoverSolver : public SetCoverSolver {
   public:
    ILPSetCoverSolver() = default;
    ~ILPSetCoverSolver() = default;

    vector<unordered_set<int>> Solve(unordered_set<int> universe, vector<unordered_set<int>> collection) override;
};
