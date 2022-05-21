#include <vector>

#include "ortools/linear_solver/linear_solver.h"

namespace operations_research {
void BasicExample() {
    // Create the linear solver with the GLOP backend.
    std::unique_ptr<MPSolver> solver(MPSolver::CreateSolver("GLOP"));

    // Create the variables x and y.

    std::vector<MPVariable*> variables;
    for (size_t i = 0; i < 2; ++i) {
        MPVariable* const x = solver->MakeNumVar(0.0, 1, "");
        variables.push_back(x);
    }

    LOG(INFO) << "Number of variables = " << solver->NumVariables();

    // Create a linear constraint, 0 <= x + y <= 2.
    MPConstraint* const ct = solver->MakeRowConstraint(0.0, 2.0, "ct");
    ct->SetCoefficient(variables[0], 1);
    ct->SetCoefficient(variables[1], 1);

    LOG(INFO) << "Number of constraints = " << solver->NumConstraints();

    // Create the objective function, 3 * x + y.
    MPObjective* const objective = solver->MutableObjective();
    objective->SetCoefficient(variables[0], 3);
    objective->SetCoefficient(variables[1], 1);
    objective->SetMaximization();

    solver->Solve();

    LOG(INFO) << "Solution:" << std::endl;
    LOG(INFO) << "Objective value = " << objective->Value();
    LOG(INFO) << "x = " << variables[0]->solution_value();
    LOG(INFO) << "y = " << variables[1]->solution_value();
}
}  // namespace operations_research

// int main() {
//     operations_research::BasicExample();
//     return EXIT_SUCCESS;
// }

#include <iostream>

#include "greedy_set_cover_solver.h"
#include "ilp_set_cover_solver.h"

int main() {
    SetCoverSolver* s = new ILPSetCoverSolver();
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