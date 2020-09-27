#include "demo_interface.h"

void interface_func(Interface *ifc) {
  ifc->bar(4);
  ifc->bar("word");
  std::string empty;
  ifc->foo(3, empty);
}
