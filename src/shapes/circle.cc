#include "circle.h"
#include <iostream>

namespace type_erasure {

Circle::Circle(double radius) : _radius{radius} {
  // std::cout << "New Circle!" << std::endl;
}

Circle::~Circle() {}

double Circle::getRadius() const noexcept { return _radius; }
void Circle::setRadius(double radius) noexcept { _radius = radius; }

} // namespace type_erasure