#include <trompeloeil.hpp>
#include "catch2/catch.hpp"

#include "demo_interface.h"

void interface_func(Interface*); // function to test

class Mock : public Interface {
public:
  MAKE_MOCK2(foo, bool(int, std::string&),override);
  MAKE_MOCK1(bar, bool(int),override);
  MAKE_MOCK1(bar, bool(std::string),override);
  MAKE_MOCK0(baz, void()); // not from Interface
};

TEST_CASE("Test interface mocks", "[mocks]") {
  using trompeloeil::_;  // wild card for matching any value
  using trompeloeil::gt; // greater-than match

  Mock m;

  trompeloeil::sequence seq1, seq2;  // control order of matching calls

  int local_var = 0;

  REQUIRE_CALL(m, bar(ANY(int)))     // expect call to m.bar(int)
    .LR_SIDE_EFFECT(local_var = _1)  // set captured variable to value of param
    .RETURN(_1 > 0)                  // return value depending on param value
    .IN_SEQUENCE(seq1)               // must be first match for seq1
    .TIMES(AT_LEAST(1));             // can be called several times

  FORBID_CALL(m, bar(0));            // but m.bar(0) is not allowed

  REQUIRE_CALL(m, bar("word"))       // expect one call to m.bar(std::string)
    .RETURN(true)
    .IN_SEQUENCE(seq2);              // must be first match for seq2

  REQUIRE_CALL(m, foo(gt(2), _))     // expect call to foo(int,std::string&)
    .WITH(_2 == "")                  // with int > 2 and empty string
    .IN_SEQUENCE(seq1, seq2)         // last for both seq1 and seq2
    .SIDE_EFFECT(_2 = "cat")         // and set param string to "cat"
    .RETURN(true);

  interface_func(&m);
  // all the above expectations must be fulfilled here
}