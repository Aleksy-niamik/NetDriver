#pragma once

#include "pico/stdlib.h"

namespace NetDriver
{
    struct HSV;
    struct RGB
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;

        RGB()
        : r(0), g(0), b(0)
        {
        }

        RGB(uint8_t rr, uint8_t gg, uint8_t bb)
            : r(rr), g(gg), b(bb)
        {
        }

        friend RGB operator*(RGB rgb, double d)
        {
            return RGB {(uint8_t)((double)rgb.r*d), (uint8_t)((double)rgb.g*d), (uint8_t)((double)rgb.b*d)};
        }

        HSV toHSV() const;
    };

    struct HSV
    {
        uint16_t h;
        uint8_t s;
        uint8_t v;

        HSV()
        : h(0), s(0), v(0)
        {
        }

        HSV(uint16_t hh, uint8_t ss, uint8_t vv)
            : h(hh), s(ss), v(vv)
        {
        }

        RGB toRGB() const;    
    };
}
