
#include <string>

class Interface {
public:
  virtual ~Interface() = default;
  virtual bool foo(int, std::string &s) = 0;
  virtual bool bar(int) = 0;
  virtual bool bar(std::string) = 0;
};
