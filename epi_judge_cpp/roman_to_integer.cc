#include <string>

using std::string;

int RomanToInteger(const string& s) {
  // Implement this placeholder.
  return 0;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"s"};
  generic_test_main(argc, argv, param_names, "roman_to_integer.tsv",
                    &RomanToInteger);
  return 0;
}
