#pragma once

#include <random>
#include <vector>

using namespace std;

vector<int> GenerateNums(int percent);
void QuickSort(vector<int>& nums, int l, int r);
int Partition(vector<int>& nums, int l, int r);
