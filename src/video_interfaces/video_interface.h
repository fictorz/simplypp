#ifndef _VIDEO_INTERFACE_H_
#define _VIDEO_INTERFACE_H_

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "../shapes/shape.h"
#include "video_interface_actions.h"

namespace type_erasure {
// will try to define many different implementation of circle serialize amongst
// many different source and headr later on!
class VideoInterface {
private:
  struct VideoInterfaceConcept {
    virtual ~VideoInterfaceConcept() {}

    virtual void drawAllShapes(std::vector<Shape> const &shapes) const = 0;
    virtual std::unique_ptr<VideoInterfaceConcept> clone() const = 0;
  };

  template <typename T> struct VideoInterfaceModel : VideoInterfaceConcept {
    VideoInterfaceModel(T &&value) : object{std::forward<T>(value)} {}

    std::unique_ptr<VideoInterfaceConcept> clone() const override {
      return std::make_unique<VideoInterfaceModel>(*this);
    }

    void drawAllShapes(std::vector<Shape> const &shapes) const override {
      ::type_erasure::drawAllShapes(object, shapes); //, /*...*/);
    }

    T object;
  };

  friend void drawAllShapes(VideoInterface const &video_interface,
                            std::vector<Shape> const &shapes) {
    video_interface.pimpl->drawAllShapes(shapes);
  }

  std::unique_ptr<VideoInterfaceConcept> pimpl;

public:
  template <typename T>
  VideoInterface(T &&x)
      : pimpl{new VideoInterfaceModel<T>(std::forward<T>(x))} {}

  // Special member functions
  VideoInterface(VideoInterface const &s);
  VideoInterface &operator=(VideoInterface const &s);
  VideoInterface(VideoInterface &&s) = default;
  VideoInterface &operator=(VideoInterface &&s) = default;
};
} // namespace type_erasure

#endif // _VIDEO_INTERFACE_H_