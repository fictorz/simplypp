module;

#include <string>
#include <iostream>

module numeric;             // ties into the numeric module



// Now define (and export) your function:
export void print(std::string message) {
  std::cout << message << std::endl;
}
