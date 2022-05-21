#include "ilp_set_cover_solver.h"

#include <ortools/linear_solver/linear_solver.h>

#include <algorithm>
#include <cmath>
#include <unordered_set>

using namespace operations_research;

vector<unordered_set<int>> ILPSetCoverSolver::Solve(unordered_set<int> universe,
                                                    vector<unordered_set<int>> collection) {
    vector<unordered_set<int>> cover;
    vector<vector<size_t>> coefficients;
    size_t max_frequency = 0;

    for (int e : universe) {
        coefficients.push_back(vector<size_t>());
        for (size_t i = 0; i < collection.size(); ++i) {
            if (collection[i].find(e) != collection[i].end()) {
                coefficients.back().push_back(i);
            }
        }
        max_frequency = max(max_frequency, coefficients.back().size());
    }

    unique_ptr<MPSolver> solver(MPSolver::CreateSolver("GLOP"));

    // Create variables.
    vector<MPVariable*> variables;
    for (size_t i = 0; i < collection.size(); ++i) {
        MPVariable* const x = solver->MakeNumVar(0.0, 1, "");
        variables.push_back(x);
    }

    // Create linear constraints.
    for (size_t i = 0; i < coefficients.size(); ++i) {
        MPConstraint* const ct = solver->MakeRowConstraint(1, MPSolver::infinity());
        for (auto c : coefficients[i]) {
            ct->SetCoefficient(variables[c], 1);
        }
    }

    // Create the objective function.
    MPObjective* const objective = solver->MutableObjective();
    for (auto v : variables) {
        objective->SetCoefficient(v, 1);
    }
    objective->SetMinimization();

    solver->Solve();

    for (size_t i = 0; i < variables.size(); ++i) {
        if (variables[i]->solution_value() >= 1.0 / max_frequency) {
            cover.push_back(collection[i]);
        }
    }

    return cover;
}
