## Sort-Merge Join details:
- Sort function: **Quicksort** (Best case: O(logn), Worst case O(n^2)). 
- Quicksort avoids unnecessary swaps which is good since our input has many duplicates. The pivot is set to the input’s middle element to avoid the worst case.
- Additionally, the on_elem flag determines if pairs are sorted by the first element before the second, or vice versa. This is because the input vectors need to be sorted by the attribute column compared in the join.


## Hash Join details
- Hashtable size = **(size of (e,f) rounded up to a power of 2) * 2**. The overallocation reduces clustering and removes the need to resize the table, but could increase IO cost if the hashtable does not fit in memory
- **Modulo** hash function is inexpensive to compute
- Probing function **p(i) = hashvalue + (i2 + i) / 2** guarantees all slots can be reached by the probe chain with table size = 2n. Therefore, every value will find a slot
- (e,f) used as the build side to minimise table size.

## Tuning Parameters - Join order
Performing the hash join before the sort-merge join reduced the MultiwayBenchmark/8192 time from 187900000 to 162300000 (3 run average)

**SMJ: (a,b) + (c,d) → res**     then     **HJ: res + (e,f) → final**

**HJ: (c,d) + (e,f) → res2**      then      **SMJ (a,b) + res2 → final**

Reasons:
- Intermediate buffer size: Res2 is likely smaller than res as (e, f) is much smaller than (a, b). This reduces the size of the buffer storing the intermediate result and therefore less page faults, improving IO performance
- Time spent on quicksort: The hashjoin with the significantly smaller table (e,f) should produce a result table (i.e. res2) that is smaller than (c,d), hence quicksort would be completed on res2 quicker than (c,d), improving CPU performance
