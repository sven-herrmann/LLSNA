#include <docopt/docopt.h>
#include <fmt/core.h>
#include <sstream>
#include <vector>

static constexpr auto USAGE =
    R"(Set Partitions

    Usage:
          set_partitions <k>
          set_partitions (-h | --help)
          set_partitions --version
 Options:
          -h --help          Show this screen.
          --version          Show version.
)";

template<typename T>
[[maybe_unused]] static inline std::string
    format_word(const std::vector<T>& word) {
  std::stringstream ss;
  ss << "[ ";
  for (const auto& a : word) {
    if (a == 0) { break; }
    ss << a << " ";
  }
  ss.seekp(word.empty() ? 0 : -1, std::ios_base::end);
  ss << " ]";
  return ss.str();
}

template<typename T>
[[maybe_unused]] static inline std::vector<std::vector<T>>
    to_set_partition(const std::vector<T>& word) {
  std::vector<T>              part = {};
  std::vector<std::vector<T>> partitions {word.size(), part};

  for (auto i = 0UL; i < word.size(); ++i) {
    partitions[word[i] - 1].push_back(i + 1);
  }
  return partitions;
}

template<typename T>
[[maybe_unused]] static inline std::string
    format_set_partition(const std::vector<std::vector<T>>& partitions) {
  std::stringstream ss;
  ss << "{ ";
  for (const auto& word : partitions) {
    if (!word.empty()) {
      ss << "{ ";
      for (const auto& a : word) {
        if (a == 0) { break; }
        ss << a << ", ";
      }
      ss.seekp(word.empty() ? -1 : -2, std::ios_base::end);
      ss << " }, ";
    }
  }
  ss.seekp(partitions.empty() ? -1 : -2, std::ios_base::end);
  ss << " }";
  return ss.str();
}

/*static inline uint64_t
    max_element(const std::vector<uint64_t>& data, const size_t max_idx) {
  auto max = 0UL;
  for (auto i = 0UL; i < max_idx; ++i) {
    max = std::max(data[i], max);
  }
  return max;
}*/

static inline int64_t allPartitions(const uint64_t sum) {
  auto                  cnt = (1 <= sum) ? 0 : -1;
  std::vector<uint64_t> partition(sum, 1);

  const auto print = [&](){
      fmt::print(
          "{:2}:  {}  {}\n",
          cnt,
          format_word(partition),
          format_set_partition(to_set_partition(partition)));
  };

  // sum == 0 is the empty set { }
  // and 1 is already done with { 1 }
  // we only have to do work for sum >= 2
  if (2 <= sum) {
    auto idx = partition.size() - 1;
    do {
      print();

      for (auto i = idx; i > 0; --i) {
        // TODO: determining max_element could probably be optimized,
        // to greatly reduce runtime
        // const auto max = max_element(partition, i);
        const auto max = *std::max_element(
            partition.begin(), partition.begin() + static_cast<long>(i));

        if (max + 1 == partition[i]) {
          partition[i] = 1;
        } else {
          ++partition[i];
          break;
        }
      }

      ++cnt;
    } while (sum != partition.back());
  }

  print();
  return ++cnt;
}

using ulong = uint64_t;

// Arndt Version
/*
class setpart {
  static constexpr size_t size = 64;
  std::array<ulong, size> x;  // setpart as RGS
  std::array<ulong, size> m;  // prefix max ...
  ulong                   n;  // m-set
public:
  explicit setpart(ulong n) : x(), m(), n(n) {
    first();
  }

  void first() {
    for (ulong j = 0; j < n; ++j) {
      x.at(j) = 1;
    }
    m.front() = 0;
    for(ulong j = 1; j < n; ++j) {
      m.at(j) = 1;
    }
  }

  bool next() {
    ulong j = n;
    while(0 < j) {
      --j;
      const ulong max = m.at(j) + 1;
      ulong v = x.at(j)+1;
      if(v <= max) {
        x.at(j) = v;
        return true;
      }
      x.at(j) = 1;
      m.at(j) = m.at(j - 1);
    }

    return false;
  }
};
*/

int main(int argc, char* argv[]) {
  const auto args = docopt::docopt(
      USAGE,
      {std::next(argv), std::next(argv, argc)},
      true,                    // show help if requested
      "Sum Partition 1.0.0");  // version string

  try {
    const auto num_elements = args.at("<k>").asLong();
    if (0 <= num_elements) {
      fmt::print("{}\n", allPartitions(static_cast<uint64_t>(num_elements)));
    }
  } catch (const std::exception&) {}
  return 0;
}
