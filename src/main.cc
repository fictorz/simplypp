#include <iostream>
#include <memory>

#include "coroutines/coroutines.h"
#include "shapes/shape.h"
#include "util/logging.h"
#include "video_interfaces/video_interface.h"

using namespace std;
using namespace type_erasure;

// Next idea is to type erase the Drawer and specify which drawer we want to
// instantiate ie: Drawer drawer = std::make_unique<OPenGL>();
// drawer.drawAllShapes(shapes);

int main() {
  LOG(INFO) << "Drawing many circles and squares.";

  VideoInterface video_interface(OpenGLInterface{4.3});
  VideoInterface video_interface2(VulcanInterface{4.3});
  using Shapes = std::vector<Shape>;

  // Creating some shapes
  Shapes shapes;
  shapes.emplace_back(Circle{2.0});
  shapes.emplace_back(Square{1.5});
  shapes.emplace_back(Circle{4.2});

  // Drawing all shapes
  drawAllShapes(video_interface, shapes);
  drawAllShapes(video_interface2, shapes);

  my_coroutine();
  my_coroutine_await();
  std::cout << "Coroutine completed\n";
}