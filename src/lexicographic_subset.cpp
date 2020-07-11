#include <docopt/docopt.h>
#include <fmt/core.h>
#include <spdlog/spdlog.h>
#include <algorithm>
#include <sstream>
#include <vector>

static constexpr int largest_representable_set = sizeof(uint64_t) * 8;

static constexpr auto USAGE =
    R"(lexicographic Subset

    Usage:
          subset_lex <num_elements> (--order-sets | --order-words)
          subset_lex (-h | --help)
          subset_lex --version
 Options:
          --order-sets       Sort output by set
          --order-words      Sort output by word-representation
          -h --help          Show this screen.
          --version          Show version.
)";

[[maybe_unused]] static inline std::string
    format_word_binary(uint64_t word, uint8_t size) {
  std::stringstream ss;

  ss << "[ ";

  for (uint16_t i = size; i > 0; --i) {
    // mask = 0x1 << (i - 1);
    auto mask = 0x1U << i;
    mask >>= 1U;

    ss << (((mask & word) == 0) ? '.' : '1');
    ss << ' ';
  }
  ss << ']';
  return ss.str();
}

[[maybe_unused]] static inline std::string
    format_word_set(uint64_t word, uint8_t size) {
  std::stringstream ss;
  ss << "{ ";

  bool is_empty_set = true;

  for (uint16_t i = size; i > 0; --i) {
    auto mask = 0x1U << i;
    mask >>= 1U;

    if ((mask & word) != 0) {
      is_empty_set = false;
      ss << std::to_string(size - i) << ", ";
    }
  }

  ss.seekp(is_empty_set ? -1 : -2, std::ios_base::end);
  ss << " }";
  return ss.str();
}

template<typename T>
[[maybe_unused]] static inline std::string
    format_word_binary(const std::vector<T>& set) {
  std::stringstream ss;

  ss << "[ ";
  for (size_t i = 0; i < set.capacity(); ++i) {
    if (std::find(std::begin(set), std::end(set), i) != std::end(set)) {
      ss << "1 ";
    } else {
      ss << ". ";
    }
  }
  ss << ']';
  return ss.str();
}

template<typename T>
[[maybe_unused]] static inline std::string
    format_word_set(const std::vector<T>& set) {
  std::stringstream ss;
  ss << "{ ";

  for (const auto& a : set) {
    ss << a << ", ";
  }

  ss.seekp(set.empty() ? -1 : -2, std::ios_base::end);
  ss << " }";
  return ss.str();
}

static inline void list_subset_in_word_order([[maybe_unused]] uint8_t k) {
  // lambda [captures](params){code}
  constexpr auto next_word = [](auto word) {
    return word + 1;
  };

  // k = 2
  // 0x1 << k => 0B0100 => 0x4
  const auto is_unfinished = [k](auto word) {
    return word < (0x1U << k);
  };

  for (uint64_t word = 0; is_unfinished(word); word = next_word(word)) {
    fmt::print(
        "{:2}:  {}  {}\n",
        word,
        format_word_binary(word, k),
        format_word_set(word, k));
  }
}

static inline void list_subset_in_set_order(uint8_t k) {
  const auto next_word = [k](auto& word) {
    if (word.empty()) {
      word.push_back(0);
      return;
    }

    // .back() returns ref to last element in word
    const auto z = word.back();
    if (z + 1 < k) {
      word.push_back(z + 1);
    } else {
      word.pop_back();
      if (!word.empty()) { ++word.back(); }
    }
  };

  const auto is_unfinished = [](const auto& word) {
    return !word.empty();
  };

  std::vector<unsigned int> subset;
  subset.reserve(k);

  uint64_t line_number = 0;
  do {
    fmt::print(
        "{:2}:  {}  {}\n",
        line_number++,
        format_word_binary(subset),
        format_word_set(subset));

    next_word(subset);
  } while (is_unfinished(subset));
}

int main(int argc, const char** argv) {
  const auto args = docopt::docopt(
      USAGE,
      {std::next(argv), std::next(argv, argc)},
      true,                         // show help if requested
      "lexicographic Subset 1.0.0");  // version string

  try {
    const auto num_elements = args.at("<num_elements>").asLong();

    if (0 <= num_elements && num_elements <= largest_representable_set) {
      const auto k = static_cast<uint8_t>(num_elements);
      if (args.at("--order-sets").asBool()) {
        list_subset_in_set_order(k);
      } else if (args.at("--order-words").asBool()) {
        list_subset_in_word_order(k);
      }
    }
  } catch (const std::exception&) {}
}
