#include "greedy_set_cover_solver.h"

#include <algorithm>
#include <iostream>
#include <unordered_set>

vector<unordered_set<int>> GreedySetCoverSolver::Solve(unordered_set<int> universe,
                                                       vector<unordered_set<int>> collection) {
    vector<unordered_set<int>> cover;

    while (!universe.empty()) {
        size_t max_size = 0;
        vector<unordered_set<int>>::iterator it = collection.begin(), max_it = it;
        while (it != collection.end()) {
            size_t size = count_if(it->begin(), it->end(), [&](int i) { return universe.find(i) != universe.end(); });
            if (size > max_size) {
                max_size = size;
                max_it = it;
            }
            ++it;
        }
        cover.push_back(*max_it);
        erase_if(universe, [&](int i) { return max_it->find(i) != max_it->end(); });
        collection.erase(max_it);
    }
    return cover;
}
