#include "yaml-cpp/yaml.h"

int main() {
    YAML::Node primes = YAML::Load("[2, 3, 5, 7, 11]");
    return 0;
}