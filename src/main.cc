import math;
import numeric;

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

int main() {
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

  std::cout << "Add: " << add(3, 4) << std::endl;
  std::cout << "Sub: " << sub(10, 6) << std::endl;

  print("test");

  //   // Using the concept-constrained template
  // Pair<double> pd{3.5, 2.0};
  // std::cout 
  //   << "sum:  " << pd.sum()  << "\n"
  //   << "diff: " << pd.diff() << "\n"
  //   << "prod: " << pd.prod() << "\n"
  //   << "quot: " << pd.quot() << "\n\n";

  // // Using the alias:
  // IntPair pi{10, 3};
  // std::cout 
  //   << "IntPair sum:  "  << pi.sum()  << "\n"
  //   << "IntPair diff: "  << pi.diff() << "\n";

}