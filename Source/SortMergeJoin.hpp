#include <stdlib.h>
#include <vector>

using namespace std;
using VectorOfPairs = std::vector<std::pair<int64_t, int64_t>>;

// Quicksort  ====================

// on_elem determines the sorting order of the input (vector of pairs)
// if on_elem == 0; sort using the first element in each pair, then sort using the second element
// if on_elem == 1; sort using the second element in each pair first, then sort using the first element
void quickSort(std::vector<std::pair<int64_t, int64_t>> &v, int low, int high,
               int on_elem) {
  int i = low, j = high;
  // Pivot as middle element
  std::pair<int64_t, int64_t> pivot = v[int((low + high) / 2)];
  // Partition
  while (i <= j) {
    while (on_elem && pivot.second > v[i].second ||
           !on_elem && pivot.first > v[i].first) {
      i++;
    }
    while (on_elem && pivot.second < v[j].second ||
           !on_elem && pivot.first < v[j].first) {
      j--;
    }
    if (i <= j) {
      std::swap(v[j], v[i]);
      i++;
      j--;
    }
  }
  // Recursion on left or right of pivot
  if (low < j) {
    quickSort(v, low, j, on_elem);
  }
  if(i < high) {
    quickSort(v, i, high, on_elem);
  }
}

// Sort-Merge Join ====================

// Given 2 sorted input tables with schema (a,b) & (c,d), joins on b == c
VectorOfPairs sortMergeJoin(VectorOfPairs& vec1, VectorOfPairs& vec2){
    VectorOfPairs result;
    auto leftI = 0;
    auto rightI = 0;
    while (leftI < vec1.size() && rightI < vec2.size()) {
        auto leftInput = vec1[leftI];
        auto rightInput = vec2[rightI];

        if(leftInput.second < rightInput.first){
            leftI++;
        } else if (leftInput.second > rightInput.first){
            rightI++;
        } else {
            // Write to output
            auto writeRightI = rightI;
            auto writeRightInput = vec2[writeRightI];
            while (leftInput.second == writeRightInput.first){
                result.emplace_back(leftInput.first, writeRightInput.second);
                if(++writeRightI < vec2.size()){
                    writeRightInput = vec2[writeRightI];
                } else {
                    break;
                }
            }
            leftI++;
        }
    }
    return result;
}
