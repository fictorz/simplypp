#ifndef _BASIC_VIDEO_INTERFACES_H_
#define _BASIC_VIDEO_INTERFACES_H_

namespace type_erasure {

class OpenGLInterface {
public:
  explicit OpenGLInterface([[maybe_unused]] double radius) {}
};

class VulcanInterface {
public:
  explicit VulcanInterface([[maybe_unused]] double side) {}
};

} // namespace type_erasure
#endif // _BASIC_VIDEO_INTERFACES_H_