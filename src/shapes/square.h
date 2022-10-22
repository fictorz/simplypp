#ifndef _SQUARE_H_
#define _SQUARE_H_

#pragma once

namespace type_erasure {

class Square {
public:
  explicit Square(double s);
  ~Square();
  double getSide() const noexcept;
  void setSide(double s) noexcept;
  // ... getCenter(), getRotation(), ...
private:
  double side;
  // ... Remaining data members
};

} // namespace type_erasure

#endif // _SQUARE_H_