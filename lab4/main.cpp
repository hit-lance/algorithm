#include <iostream>

#include "quicksort.h"

int main() {
    // vector<int> nums = {4, 6, 1, 3, 2, 5};

    auto nums = GenerateNums(100);
    QuickSort(nums, 0, 5);
    for (auto& n : nums) {
        cout << n << " ";
    }
    cout << endl;
    return 0;
}