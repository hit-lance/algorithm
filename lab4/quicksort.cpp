#include "quicksort.h"

#include <algorithm>

random_device rd;
mt19937 gen(rd());

vector<int> GenerateNums(int percent) {
    const int N = 1e6;
    int dup_num = N * percent / 100;
    vector<int> nums(dup_num);
    for (int i = 1; i <= N - dup_num; ++i) {
        nums.push_back(i);
    }
    shuffle(nums.begin(), nums.end(), gen);
    return nums;
}

bool Compare(int a, int b) {
    bernoulli_distribution d(0.5);
    return (d(rd)) ? a < b : a <= b;
}

void QuickSort(vector<int>& nums, int l, int r) {
    if (l < r) {
        int p = Partition(nums, l, r);
        QuickSort(nums, l, p - 1);
        QuickSort(nums, p + 1, r);
    }
}

int Partition(vector<int>& nums, int l, int r) {
    uniform_int_distribution<int> unif(l, r);

    int t = unif(rd);
    int pivot = nums[t];
    swap(nums[t], nums[l]);

    int p = l, q = r;
    while (p < q) {
        while (p < q && Compare(pivot, nums[q])) {
            --q;
        }
        swap(nums[p], nums[q]);
        while (p < q && Compare(nums[p], pivot)) {
            ++p;
        }
        swap(nums[p], nums[q]);
    }
    nums[p] = pivot;
    return p;
}
