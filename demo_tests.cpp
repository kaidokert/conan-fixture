#define CATCH_CONFIG_MAIN
#include <vector>

#include <catch2/catch.hpp>

SCENARIO("This works", "[foo]") {
  constexpr size_t v_size = 5;
  constexpr size_t v_bigsize = 10;

  GIVEN("something") {
    std::vector<int> v(v_size);
    REQUIRE(v.size() == v_size);

    WHEN("the size is increased") {
      v.resize(v_bigsize);

      THEN("the size and capacity change") {
        REQUIRE(v.size() == v_bigsize);
        REQUIRE(v.capacity() >= v_bigsize);
      }
    }
  }
}
