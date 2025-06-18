#include "square.h"

namespace type_erasure {

Square::Square(double s)
    : side{s} // ... Remaining data members
{}
Square::~Square() {}

double Square::getSide() const noexcept { return side; }
void Square::setSide(double s) noexcept { side = s; }

} // namespace type_erasure