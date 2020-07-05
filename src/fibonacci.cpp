#include "constexpr_sqrt.hpp"

#include <complex>
#include <docopt/docopt.h>
#include <fmt/core.h>

static constexpr auto USAGE =
    R"(Fibonacci number calculation

    Usage:
          fibonacci -- <real> <imag>
          fibonacci -- <real>
          fibonacci (-h | --help)
          fibonacci --version
 Options:
          -h --help          Show this screen.
          --version          Show version.
)";

static constexpr auto sqrt5 = Constexpr::sqrt(5);
static constexpr auto phi   = (1 + sqrt5) / 2;
static constexpr auto n_phi = (1 - sqrt5) / 2;

std::complex<double> fib(const std::complex<double>& n) {
  return (std::pow(phi, n) - std::pow(n_phi, n)) / sqrt5;
}

int main(int argc, char* argv[]) {
  const auto args = docopt::docopt(
      USAGE,
      {std::next(argv), std::next(argv, argc)},
      true,                                  // show help if requested
      "Fibonacci Number generation 1.0.0");  // version string

  try {
    const auto real_part = args.at("<real>");

    std::complex<double> n {double(real_part.asLong())};

    try {
      const auto imag_part = args.at("<imag>");
      n.imag(double(imag_part.asLong()));
    } catch (const std::exception&) {}

    const auto fib_n = fib(n);

    const auto precision = 4;
    fmt::print(
        "Fib({1:.{0}f} {2:+.{0}f}i) =  {3:.{0}f} {4:+.{0}f}i\n",
        precision,
        n.real(),
        n.imag(),
        fib_n.real(),
        fib_n.imag());

  } catch (const std::exception& ex) { fmt::print("{}\n", ex.what()); }
  return 0;
}
