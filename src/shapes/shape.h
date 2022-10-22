// Copyright (c) Elixir Tech Inc. All Rights Reserved.

#ifndef _SHAPES_H_
#define _SHAPES_H_

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "shape.tpp"

namespace type_erasure {

class Shape;
template <typename T>
struct IsShape : public std::is_same<Shape, std::decay_t<T>> {};
// The idea is to define many different implementation of circle serialize
// amongst many different source and header later on!
class Shape {
private:
  struct ShapeConcept {
    virtual ~ShapeConcept() {}

    virtual void serialize(/*...*/) const = 0;
    virtual void draw(/*...*/) const = 0;
    virtual void scale(double scale_factor) = 0;
    virtual std::unique_ptr<ShapeConcept> clone() const = 0;
  };

  template <typename T> struct ShapeModel : ShapeConcept {
    ShapeModel(T &&value) : object{std::forward<T>(value)} {}

    std::unique_ptr<ShapeConcept> clone() const override {
      return std::make_unique<ShapeModel>(*this);
    }

    void serialize(/*...*/) const override {
      ::type_erasure::serialize(object); //, /*...*/);
    }

    void draw(/*...*/) const override {
      ::type_erasure::draw(object); //, /*...*/);
    }

    void scale(double scale_factor) override {
      ::type_erasure::scale(object, scale_factor);
    }

    T object;
  };

  friend void serialize(Shape const &shape) { shape.pimpl->serialize(); }
  friend void draw(Shape const &shape) { shape.pimpl->draw(); }
  friend void scale(Shape &shape, double scale_factor) {
    shape.pimpl->scale(scale_factor);
  }

  std::unique_ptr<ShapeConcept> pimpl;

public:
  template <typename T, typename = std::enable_if_t<!IsShape<T>::value>>
  Shape(T &&x) : pimpl{new ShapeModel<T>(std::forward<T>(x))} {}

  // Special member functions
  Shape(Shape const &s) : pimpl{s.pimpl->clone()} {}
  Shape &operator=(Shape const &s) {
    this->pimpl = s.pimpl->clone();
    return *this;
  }
  Shape(Shape &&s) { std::swap(this->pimpl, s.pimpl); }
  Shape &operator=(Shape &&s) {
    std::swap(this->pimpl, s.pimpl);
    return *this;
  }
};
} // namespace type_erasure

#endif // _SHAPES_H_