# LLSNA

Project to keep my progress for the course low-level and semi-numeric algorithms.
And some other interesting bits.

Implemented thus far:
  - a [prime test](src/small_prime.cpp) with O(1) for n less or equal to 64
  - a fast popcnt implementation [num_set_bits](src/num_set_bits.cpp)
  - fast [lexicographic subset](src/lexicographic_subset.cpp):
    - ordered by the binary word representing the set
    - ordered by the set itself
  - fast integer composition [sum_composition](src/sum_composition.cpp)
  - fast integer partition [sum_partition](src/sum_partition.cpp)
  - fast [set_partitions](src/set_partitions.cpp)
  - [mixed radix gray code counting](src/mixed_radix_gray_codes.cpp)
  - O(1) [Fibonacci number](src/fibonacci.cpp) using Binet's formula for real or even complex `n`
  - [compile time square-root](src/constexpr_sqrt.hpp)
