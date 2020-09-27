#include "yaml-cpp/yaml.h"

auto main() -> int { // NOLINT(bugprone-exception-escape)
  YAML::Node primes = YAML::Load("[2, 3, 5, 7, 11]");
  printf("Yay %d!\n", static_cast<int>(primes.IsSequence()));
  for (auto el = primes.begin(); el != primes.end(); ++el) {
    int num = el->as<int>();
    printf("%d\n", num);
  }
  return 0;
}
