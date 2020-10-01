#include <cstdint>

constexpr uint64_t ENTRY(uint8_t x) {
  return 1UL << x;
}

constexpr static uint64_t primes = ENTRY(2U)     //
                                   | ENTRY(3U)   //
                                   | ENTRY(5U)   //
                                   | ENTRY(7U)   //
                                   | ENTRY(11U)  //
                                   | ENTRY(13U)  //
                                   | ENTRY(17U)  //
                                   | ENTRY(19U)  //
                                   | ENTRY(23U)  //
                                   | ENTRY(29U)  //
                                   | ENTRY(31U)  //
                                   | ENTRY(37U)  //
                                   | ENTRY(41U)  //
                                   | ENTRY(43U)  //
                                   | ENTRY(47U)  //
                                   | ENTRY(53U)  //
                                   | ENTRY(59U)  //
                                   | ENTRY(61U);

constexpr static uint8_t max_bits = sizeof(decltype(primes)) * 8 - 1;

static inline bool sieve([[maybe_unused]] uint8_t x) {
  return false;  // TODO: implement me
}

[[maybe_unused]] static inline bool is_small_prime(uint8_t x) {
  if (x < max_bits) { return 0 != (primes & ENTRY(x)); }
  return sieve(x);
}

int main() {
  // TODO: implement me
  return 0;
}
