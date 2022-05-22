#include <iostream>

#include "quicksort.h"

int main() {
    // vector<int> nums = {4, 6, 1, 3, 2, 5};

    auto nums = GenerateNums(10);
    QuickSort(nums, 0, nums.size());

    cout << "done" << endl;
    return 0;
}