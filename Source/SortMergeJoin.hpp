#include <stdlib.h>
#include <vector>

using namespace std;
using VectorOfPairs = std::vector<std::pair<int64_t, int64_t>>;

// Quicksort & Associated Helper Functions --------------

int partition(VectorOfPairs& v, int low, int high, int on_elem){
    std::pair<int64_t, int64_t> pivot = v[high];
    int i = low-1;
    for (int j = low; j < high; j++) {
        if (on_elem && pivot.second > v[j].second || !on_elem && pivot.first > v[j].first) {
            // Smaller than pivot, so swap
            i++;
            std::swap(v[i], v[j]);
        }
    }
    if (i + 1 < v.size()-1){
        std::swap(v[i + 1], v[high]);
    }
    // Return partition point
    return (i + 1);
}

void quickSort(VectorOfPairs& v, int low, int high, int on_elem) {
    if (low < high) {
        int p = partition(v, low, high, on_elem);
        // Recurse on the left of pivot
        quickSort(v, low, p - 1, on_elem);
        // Recurse on the right of pivot
        quickSort(v, p + 1, high, on_elem);
    }
}

// Sort-Merge Join -------------

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
