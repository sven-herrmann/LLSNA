#include <limits>

/*
 * According to https://stackoverflow.com/a/34134071
 */

namespace Detail {
  double constexpr sqrtNewtonRaphson(double x, double curr, double prev) {
    return curr == prev ? curr
                        : sqrtNewtonRaphson(x, (curr + x / curr) / 2, curr);
  }
}  // namespace Detail

namespace Constexpr {
  /*
   * Constexpr version of the square root
   * Return value:
   *   - For a finite and non-negative value of "x", returns an approximation
   * for the square root of "x"
   *   - Otherwise, returns NaN
   */
  double constexpr sqrt(double x) {
    return x >= 0 && x < std::numeric_limits<double>::infinity()
               ? Detail::sqrtNewtonRaphson(x, x, 0)
               : std::numeric_limits<double>::quiet_NaN();
  }
}  // namespace Constexpr
