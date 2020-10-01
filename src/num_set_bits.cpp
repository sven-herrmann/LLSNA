#include <cassert>
#include <cstdint>
#include <fmt/core.h>

inline uint8_t num_set_bits(uint64_t x) {
#ifdef CPP20
#  include <bit>
  return std::popcount(x);
}
#else
  // x = (0x5555555555555555ul & x) + (0x5555555555555555ul & (x>> 1));
  // x = (0x3333333333333333ul & x) + (0x3333333333333333ul & (x>> 2));
  // x = (0x0f0f0f0f0f0f0f0ful & x) + (0x0f0f0f0f0f0f0f0ful & (x>> 4));
  // x = (0x00ff00ff00ff00fful & x) + (0x00ff00ff00ff00fful & (x>> 8));
  // x = (0x0000ffff0000fffful & x) + (0x0000ffff0000fffful & (x>>16));
  // x = (0x00000000fffffffful & x) + (0x00000000fffffffful & (x>>32));

  x -= (x >> 1U) & 0x5555555555555555UL;       // NOLINT
  x = ((x >> 2U) & 0x3333333333333333UL)       // NOLINT
      + (x & 0x3333333333333333UL);            // NOLINT
  x = ((x >> 4U) + x) & 0x0f0f0f0f0f0f0f0fUL;  // NOLINT
  x *= 0x0101010101010101UL;  // NOLINT  propably only up to 256bit
  x >>= 56U;                  // NOLINT 24 for uint32_t;

  assert(x <= 64);

  return static_cast<uint8_t>(x);
}
#endif

int main() {
  for (uint64_t i = 0; i <= 0xffUL; ++i) {  // NOLINT
    fmt::print("{0:3} = {0:#04x}: {1}\n", i, num_set_bits(i));
  }
  return 0;
}
