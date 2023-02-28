// Online C++ compiler to run C++ program online
#include <iostream>
#include <vector>
#include <utility>
#include <optional>
#include <stdlib.h>

using VectorOfPairs = std::vector<std::pair<int64_t, int64_t>>;

VectorOfPairs hashJoin(VectorOfPairs& buildSide, VectorOfPairs& probeSide) {

  // bit twiddling that rounds buildSide.size() up to the nearest power of 2
  size_t tableSize = buildSide.size() - 1;
  tableSize |= tableSize >> 1;
  tableSize |= tableSize >> 2;
  tableSize |= tableSize >> 4;
  tableSize |= tableSize >> 8;
  tableSize |= tableSize >> 16;
  tableSize++;

  // hash table size should be at least twice the size of table 1
  tableSize <<= 1;
  std::vector<std::optional<std::pair<int64_t, int64_t>>> hashtable (tableSize);
  std::cout << "table size is " << tableSize << std::endl;

  // building hash table
  for (int i = 0; i < buildSide.size(); i++) {
    auto& tuple = buildSide[i];
    size_t pos = abs(int(tuple.first % tableSize));
    size_t step = 1;
    while (hashtable[pos % tableSize].has_value()) {
      // quadratic probing with triangle numbers
      // with table size = 2^n, every slot can be visited by the probe chain
      pos += step;
      step++;
    }
    hashtable[pos % tableSize] = tuple;
  }

  VectorOfPairs result;

  // probing hash table
  for (int i = 0; i < probeSide.size(); i++) {
    auto& tuple = probeSide[i];
    size_t pos = abs(int(tuple.second % tableSize));
    size_t step = 1;
    while (hashtable[pos % tableSize].has_value()) {
      auto& entry = hashtable[pos % tableSize].value();
      if (entry.first == tuple.second) {
        result.emplace_back(tuple.first, entry.second);
      }
      pos += step;
      step++;
    }
  }
  
  for (int i = 0; i < tableSize; i++) {
    int64_t a = -1; int64_t b = -1;
    if (hashtable[i].has_value()) {
      a = hashtable[i].value().second;
      b = hashtable[i].value().first;
    }
      printf("%ld, %ld\n", a, b);
  }
    
  return result;
}