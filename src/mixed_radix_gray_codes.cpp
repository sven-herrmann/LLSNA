#include <docopt/docopt.h>
#include <fmt/core.h>
#include <sstream>

static constexpr auto USAGE =
    R"(Mixed Radix Gray Codes

    Usage:
          mixed_radix_gray_codes -- <digit_radix>...
          mixed_radix_gray_codes (-h | --help)
          mixed_radix_gray_codes --version
 Options:
          -h --help          Show this screen.
          --version          Show version.
)";

/**
 * \brief Helper Enum for counting directions
 */
enum class Direction { Up, Down };

/**
 * \brief just for some nice formated output
 * \param[in]  word the mixed-radix number to be formated
 */
template<typename T>
[[maybe_unused]] static inline std::string
    format_word(const std::vector<T>& word) {
  std::stringstream ss;
  ss << "[ ";
  for (const auto& a : word) {
    ss << a << ", ";
  }
  ss.seekp(word.empty() ? 0 : -2, std::ios_base::end);
  ss << " ]";
  return ss.str();
}

/**
 * \brief lists all numbers. Every digit is counted from 0 towards its radix
 * \param[in]  radices radix per position radix[0] is most significant digit
 */
void all_numbers(const std::vector<int>& radices) {
  std::vector<int>       number(radices.size());
  std::vector<Direction> direction(radices.size());

  // ensure a correct initial counting direction
  std::transform(
      radices.begin(), radices.end(), direction.begin(), [](const auto& s) {
        return s >= 0 ? Direction::Up : Direction::Down;
      });

  // save the first direction the least significant digit will take for later
  const auto firstDir = direction.back();

  // we are done when the direction of the least significant digit has changed
  while (firstDir == direction.back()) {
    fmt::print("{}\n", format_word(number));

    for (auto i = 0U; i < number.size(); ++i) {
      if (direction[i] == Direction::Up) {
        if (number[i] == std::max(radices[i]-1, 0)) {
          // change direction and move to the next digit
          direction[i] = Direction::Down;
        } else {
          // increment current digit and continue
          ++number[i];
          break;
        }
      } else {
        if (number[i] == std::min(radices[i]+1, 0)) {
          // change direction and move to the next digit
          direction[i] = Direction::Up;
        } else {
          // decrement current digit and continue
          --number[i];
          break;
        }
      }
    }
  }
}

int main(int argc, char* argv[]) {
  const auto args = docopt::docopt(
      USAGE,
      {std::next(argv), std::next(argv, argc)},
      true,                             // show help if requested
      "Mixed Radix Gray Codes 1.0.0");  // version string

  try {
    const auto digit_radix = args.at("<digit_radix>");
    if (digit_radix.isStringList()) {
      const auto&      digit_radix_list = digit_radix.asStringList();
      std::vector<int> radices(digit_radix_list.size());

      // get those numbers out of the Strings
      std::transform(
          digit_radix_list.begin(),
          digit_radix_list.end(),
          radices.begin(),
          [](const auto& s) {
            return std::stoi(s);
          });
      all_numbers(radices);
    }
  } catch (const std::exception&) {}
  return 0;
}
