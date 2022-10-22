#include <gtest/gtest.h>

#include <iostream>
#include <memory>

#include "shapes/shape.h"
#include "util/logging.h"
#include "video_interfaces/video_interface.h"

using namespace std;
using namespace type_erasure;

// Next idea is to type erase the Drawer and specify which drawer we want to
// instantiate ie: Drawer drawer = std::make_unique<OPenGL>();
// drawer.drawAllShapes(shapes);
TEST(TestShapes, mainShapesTest) {

  LOG(INFO) << "Drawing many circles and squares.";

  VideoInterface video_interface(OpenGLInterface{4.3});
  VideoInterface video_interface2(VulcanInterface{4.3});

  using Shapes = std::vector<Shape>;

  LOG(INFO) << "== Creating a list of shapes\n";
  Shapes shapes;
  shapes.reserve(10); // prevent vector resize and redundant prints
  LOG(INFO) << "== Adding 3 shapes\n";
  shapes.emplace_back(Circle{2.0});
  shapes.emplace_back(Square{1.5});
  shapes.emplace_back(Circle{4.2});

  LOG(INFO) << "== Drawing a list of shapes\n";
  drawAllShapes(video_interface, shapes);
  drawAllShapes(video_interface2, shapes);

  LOG(INFO) << "== Copying a list of shapes\n";
  auto shapes_scaled = shapes; // copy shapes, here clone() is used

  for (auto &shape : shapes_scaled)
    scale(shape, 10);

  LOG(INFO) << "== Drawing the copied list of shapes\n";
  drawAllShapes(video_interface, shapes_scaled); // scaled by factor 10
  LOG(INFO) << "== Drawing the original list of shapes\n";
  drawAllShapes(video_interface, shapes); // left untouched

  LOG(INFO) << "== Create new shape\n";
  Shape circle1(Circle{2.0});
  draw(circle1);

  LOG(INFO) << "== Moving the shape\n";
  Shape circle2{std::move(circle1)};
  draw(circle2);

  LOG(INFO) << "== Copying the shape\n";
  Shape circle3{circle2};
  draw(circle3);

  LOG(INFO) << "== Assigning a shape\n";
  circle1 = circle2;
  draw(circle1);

  LOG(INFO) << "== Move assigning a shape\n";
  circle1 = std::move(circle3);
  draw(circle1);

  // Try to make a vector of shape and draw them all
}
