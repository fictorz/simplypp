// Copyright (c) Elixir Tech Inc. All Rights Reserved.

#ifndef _VIDEO_ERASED_TYPE_SHAPES_H_
#define _VIDEO_ERASED_TYPE_SHAPES_H_

#include <vector>
#include <memory>
#include <string>
#include <iostream>

#include "basic_shapes.h"

namespace type_erasure {

    void serialize(Circle const&)
    {
        // std::cout << "erased_type Shape Circle serialize " << '\n';
    }

    void draw(Circle const&)
    {
        // std::cout << "erased_type Shape Circle draw " << '\n';
    }

    void scale(Circle &circle, double scale_factor)
    {
        circle.setRadius(circle.getRadius() * scale_factor);
    }

    void serialize(Square const&)
    {
        // std::cout << "erased_type Shape Square serialize " << '\n';
    }

    void draw(Square const&)
    {
        // std::cout << "erased_type Shape Square draw " << '\n';
    }

    void scale(Square &square, double scale_factor)
    {
        square.setSide(square.getSide() * scale_factor);
    }

}


#endif // _VIDEO_ERASED_TYPE_SHAPES_H_