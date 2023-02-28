#include <vector>
#include <optional>

using VectorOfPairs = std::vector<std::pair<int64_t, int64_t>>;

VectorOfPairs hashJoin(VectorOfPairs& buildSide, VectorOfPairs& probeSide) {
  // Bit twiddling that rounds buildSide.size() up to the nearest power of 2
  size_t tableSize = buildSide.size() - 1;
  tableSize |= tableSize >> 1;
  tableSize |= tableSize >> 2;
  tableSize |= tableSize >> 4;
  tableSize |= tableSize >> 8;
  tableSize |= tableSize >> 16;
  tableSize++;

  // Hash table size should be at least twice of buildSide.size()
  tableSize <<= 1;
  std::vector<std::optional<std::pair<int64_t, int64_t>>> hashTable (tableSize);

  // Building hash table
  for (int i = 0; i < buildSide.size(); i++) {
    auto& tuple = buildSide[i];
    // Hash function: modulo tableSize
    size_t pos = abs(int(tuple.first % tableSize));
    size_t step = 1;
    while (hashTable[pos % tableSize].has_value()) {
      // Quadratic probing with triangle numbers (distance from original slot goes 1, 3, 6, 10...)
      // With table size = 2^n, every slot can be visited by the probe chain
      pos += step;
      step++;
    }
    hashTable[pos % tableSize] = tuple;
  }

  VectorOfPairs result;

  // Probing hash table
  for (int i = 0; i < probeSide.size(); i++) {
    auto& tuple = probeSide[i];
    size_t pos = abs(int(tuple.second % tableSize));
    size_t step = 1;
    while (hashTable[pos % tableSize].has_value()) {
      auto& entry = hashTable[pos % tableSize].value();
      if (entry.first == tuple.second) {
        result.emplace_back(tuple.first, entry.second);
      }
      pos += step;
      step++;
    }
  }
    
  return result;
}
