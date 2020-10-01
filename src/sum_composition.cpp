#include <cstddef>
#include <docopt/docopt.h>
#include <vector>
#include <fmt/core.h>
#include <sstream>

static constexpr auto USAGE =
    R"(Sum Composition

    Usage:
          sum_composition <sum>
          sum_composition (-h | --help)
          sum_composition --version
 Options:
          -h --help          Show this screen.
          --version          Show version.
)";

template<typename T>
[[maybe_unused]] static inline std::string
    format_word_binary(const std::vector<T>& word) {
  std::stringstream ss;

  ss << "[ ";
  for (auto i = 0UL; i < word.size(); ++i) {
    if (1 <= word[i]) {
      for (auto j = word[i]; j > 1; --j) {
        ss << "1 ";
      }
      ss << ". ";
    }
  }

  ss.seekp(word.empty() ? -1 : -2, std::ios_base::end);
  ss << ']';
  return ss.str();
}

template <typename T>
[[maybe_unused]] static inline std::string
    format_word_set(const std::vector<T>& word) {
  std::stringstream ss;
  ss << "{ ";
  for (const auto& a : word) {
    if (a == 0) { break; }
    ss << a << ", ";
  }
  ss.seekp(word.empty() ? -1 : -2, std::ios_base::end);
  ss << " }";
  return ss.str();
}

static inline void allCompositions(const size_t sum) {
  auto                cnt = (1 <= sum) ? 0 : -1;
  std::vector<size_t> combination(sum, 1);

  if (2 <= sum) {
    size_t idx = combination.size() - 1;
    do {
      // PRINT(combination);
      fmt::print(
          "{:2}:  {}  {}\n",
          cnt,
          format_word_binary(combination),
          format_word_set(combination));

      auto& z = combination[idx];
      auto& y = combination[idx - 1];

      ++y;
      --z;

      if (0 != z) {
        const auto width = z;
        const auto from  = combination.begin() + static_cast<long>(idx);
        std::fill(from, from + static_cast<long>(width), 1);
        idx += width;
      }

      --idx;
      ++cnt;
    } while (sum != combination.front());
  }

  fmt::print(
      "{:2}:  {}  {}\n",
      cnt,
      format_word_binary(combination),
      format_word_set(combination));
}

int main(int argc, char* argv[]) {
  const auto args = docopt::docopt(
      USAGE,
      {std::next(argv), std::next(argv, argc)},
      true,                      // show help if requested
      "Sum Composition 1.0.0");  // version string

  try {
    const auto num_elements = args.at("<sum>").asLong();

    if (0 <= num_elements) {
      const auto k = static_cast<size_t>(num_elements);
      allCompositions(k);
    }
  } catch (const std::exception&) {}
  return 0;
}
