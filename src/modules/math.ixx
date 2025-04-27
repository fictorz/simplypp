export module math;

// A simple calculator class
export class Calculator {
public:
  Calculator() = default;

  // Add two ints
  int add(int a, int b) const { return a + b; }

  // Subtract b from a
  int sub(int a, int b) const { return a - b; }
};

// Free-function aliases
export inline int add(int a, int b) { return Calculator{}.add(a,b); }
export inline int sub(int a, int b) { return Calculator{}.sub(a,b); }