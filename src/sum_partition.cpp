#include <docopt/docopt.h>
#include <fmt/core.h>
#include <sstream>
#include <vector>

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

static inline int64_t allPartitions(const int64_t sum) {
  auto                 cnt = (1 <= sum) ? 0 : -1;
  std::vector<int64_t> partition(static_cast<size_t>(sum), 1);

  // sum == 0 is the empty set { }
  // and 1 is already done with { 1 }
  // we only have to do work for sum >= 2
  if (2 <= sum) {
    auto idx = partition.size() - 1;
    do {
      fmt::print("{:2}:  {}\n", cnt, format_word_set(partition));

      auto& z = partition[idx];
      auto& y = partition[idx - 1];

      if (const auto diff = z - y; diff < 2) {
        // easy case: move z onto y, y bekomes next z
        y += z;
        z = 0;
        --idx;
      } else {
        // we have to move one onto y,
        // determine what we have to move to the left,
        // and have to determine our next y and z
        auto to_move = z - 1;
        y += 1;
        z = 0;
        // put as much as we can to the left
        // 2 * y to check if we can place atleast 2 more y
        while (2 * y <= to_move) {
          partition[idx] = y;
          ++idx;
          to_move -= y;
        }
        // put the remainder onto our new z
        partition[idx] += to_move;
      }
      ++cnt;
    } while (sum != partition.front());
  }

  fmt::print("{:2}:  {}\n", cnt, format_word_set(partition));
  return ++cnt;
}

int main(int argc, char* argv[]) {
  const auto args = docopt::docopt(
      USAGE,
      {std::next(argv), std::next(argv, argc)},
      true,                    // show help if requested
      "Sum Partition 1.0.0");  // version string

  try {
    const auto num_elements = args.at("<sum>").asLong();

    if (0 <= num_elements) { fmt::print("{}\n", allPartitions(num_elements)); }
  } catch (const std::exception&) {}
  return 0;
}
