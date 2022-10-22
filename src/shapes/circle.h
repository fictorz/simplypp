#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#pragma once

namespace type_erasure {

class Circle {
public:
  explicit Circle(double radius);
  ~Circle();
  double getRadius() const noexcept;
  void setRadius(double radius) noexcept;
  // ... getCenter(), getRotation(), ...
private:
  double _radius;
  // ... Remaining data members
};

} // namespace type_erasure

#endif // _CIRCLE_H_