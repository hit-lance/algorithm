#include <iostream>

#include "greedy_set_cover_solver.h"
#include "ilp_set_cover_solver.h"

int main() {
    // auto [universe, collection] = GenerateSet(2000);
    unordered_set<int> universe{1, 2, 3, 4, 5};
    vector<unordered_set<int>> collection{{1, 2, 3}, {2, 4}, {3, 4}, {4, 5}};

    SetCoverSolver* s1 = new GreedySetCoverSolver();
    vector<unordered_set<int>> cover1 = s1->Solve(universe, collection);
    SetCoverSolver* s2 = new ILPSetCoverSolver();
    vector<unordered_set<int>> cover2 = s2->Solve(universe, collection);

    for (auto& s : cover1) {
        for (auto item : s) {
            cout << item << " ";
        }
        cout << endl;
    }

    for (auto& s : cover2) {
        for (auto item : s) {
            cout << item << " ";
        }
        cout << endl;
    }
    return 0;
}