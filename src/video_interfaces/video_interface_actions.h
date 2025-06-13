#ifndef _VIDEO_INTERFACE_ACTIONS_H_
#define _VIDEO_INTERFACE_ACTIONS_H_

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "../shapes/shape.h"
#include "basic_video_interfaces.h"

namespace type_erasure {

void drawAllShapes([[maybe_unused]] OpenGLInterface const &opengl,
                   std::vector<Shape> const &shapes) //, /*...*/ );
{
  // std::cout << "opengl Shape draw " << '\n';
  for (auto const &shape : shapes) {
    draw(shape);
  }
}

void drawAllShapes([[maybe_unused]] VulcanInterface const &vulcan,
                   std::vector<Shape> const &shapes) //, /*...*/ );
{
  // std::cout << "vulcan Shape draw " << '\n';
  for (auto const &shape : shapes) {
    draw(shape);
  }
}
} // namespace type_erasure

#endif // _VIDEO_INTERFACE_ACTIONS_H_