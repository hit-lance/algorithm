#include <iostream>

#include "greedy_set_cover_solver.h"

int main() {
    SetCoverSolver* s = new GreedySetCoverSolver();
    unordered_set<int> universe{1, 2, 3, 4, 5};
    vector<unordered_set<int>> collection{{1, 2, 3}, {2, 4}, {3, 4}, {4, 5}};
    vector<unordered_set<int>> cover = s->Solve(universe, collection);
    for (auto& s : cover) {
        for (auto item : s) {
            cout << item << " ";
        }
        cout << endl;
    }
    return 0;
}