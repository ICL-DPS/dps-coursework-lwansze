#include <stdlib.h>
#include <vector>

using namespace std;
using VectorOfPairs = std::vector<std::pair<int64_t, int64_t>>;

// Quicksort & Associated Helper Functions --------------

// Given 2 pairs a and b, returns 1 if a > b, 0 if a == b and -1 if a < b
// If on_elem == 0; first element in the pair is compared first
// If on_elem == 1; second element in the pair is compared first
int compare_pair(std::pair<int64_t, int64_t> a, std::pair<int64_t, int64_t> b, int on_elem){
    int a_f = a.first, a_s = a.second;
    int b_f = b.first, b_s = b.second;
    if(on_elem) {
        // Compare on second element in pair first
        if((a_s > b_s) || (a_s == b_s && a_f > b_f)){
            return 1;
        } else if ((a_s < b_s) || (a_s == b_s && a_f < b_f)){
            return -1;
        } else {
            return 0;
        }
    } else{
        // Compare on first element in pair first
        if((a_f > b_f) || (a_f == b_f && a_s > b_s)){
            return 1;
        } else if ((a_f < b_f) || (a_f == b_f && a_s < b_s)){
            return -1;
        } else {
            return 0;
        }
    }
}

int partition(VectorOfPairs& v, int low, int high, int on_elem){
    std::pair<int64_t, int64_t> pivot = v[high];
    int i = low-1;
    for (int j = low; j < high; j++) {
        if (compare_pair(pivot, v[j], on_elem) != -1) {
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
