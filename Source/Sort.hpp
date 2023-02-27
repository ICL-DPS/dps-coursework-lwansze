#include <stdlib.h>
#include <vector>

using namespace std;

// Quicksort vector of pairs.
// Sort either on first elem or second elem in the pair; set using elem

// returns 1 if a > b, 0 if a == b and -1 if a < b
int compare_pair(std::pair<int64_t, int64_t> a, std::pair<int64_t, int64_t> b,){
    if (a.first == b.first){
        if (a.second > b.second){
            return 1;
        } else if (a.second < b.second){
            return -1;
        } else{
            return 0;
        }
    } else if (a.first > b.first){
        return 1;
    }
    return -1;
}

int partition(std::vector<std::pair<int64_t, int64_t>>& v, int low, int high){
    std::pair<int64_t, int64_t> pivot = v[high];
    int i = low-1;
    for (int j = low; j < high; j++) {
        if (compare_pair(pivot, v[j]) != -1) {
             
            // elem smaller than pivot, so swap
            i++;
            std::swap(v[i], v[j]);
        }
    }
    //std::cout << i;
    if (i + 1 < v.size()-1){
        std::swap(v[i + 1], v[high]);
    }
    // return partition point
    
    return (i + 1);
}

void quickSort(std::vector<std::pair<int64_t, int64_t>>& v, int low, int high) {
    if (low < high) {
        int p = partition(v, low, high);
        // Recurse on the left of pivot
        quickSort(v, low, p - 1);
        // Recurse on the right of pivot
        quickSort(v, p + 1, high);
    }
}
