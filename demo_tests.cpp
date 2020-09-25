#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include <vector>

SCENARIO( "This works", "[foo]" ) {
    GIVEN("something") {
        std::vector<int> v(5);
        REQUIRE( v.size() == 5 );

        WHEN( "the size is increased" ) {
            v.resize( 10 );

            THEN( "the size and capacity change" ) {
                REQUIRE( v.size() == 10 );
                REQUIRE( v.capacity() >= 10 );
                //REQUIRE( 1 == 2 );
            }
        }
    }
}