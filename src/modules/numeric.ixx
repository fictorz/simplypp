module;                 // ← marks the global module fragment

export module numeric;  // ← must come next

#include <iostream>
// import <iostream>; // Import iostream as a module
// import string;

// Only declarations here—no includes!
export void print(std::string message);
