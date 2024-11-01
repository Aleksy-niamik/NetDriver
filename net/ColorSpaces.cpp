
#include "ColorSpaces.h"

using namespace NetDriver;

RGB HSV::toRGB() const
{
    double      hh, p, q, t, ff;
    long        i;
    double r,g,b;

    hh = h;
    if(hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = v / 100.0f * (1.0 - s / 100.0f);
    q = v / 100.0f * (1.0 - (s / 100.0f * ff));
    t = v / 100.0f * (1.0 - (s / 100.0f * (1.0 - ff)));

    switch(i)
    {
    case 0:
        r = v / 100.0f;
        g = t;
        b = p;
        break;
    case 1:
        r = q;
        g = v / 100.0f;
        b = p;
        break;
    case 2:
        r = p;
        g = v / 100.0f;
        b = t;
        break;

    case 3:
        r = p;
        g = q;
        b = v / 100.0f;
        break;
    case 4:
        r = t;
        g = p;
        b = v / 100.0f;
        break;
    case 5:
    default:
        r = v / 100.0f;
        g = p;
        b = q;
        break;
    }
    RGB rgb;
    rgb.r = 255*r;
    rgb.g = 255*g;
    rgb.b = 255*b;

    return rgb;
}

HSV RGB::toHSV() const
{
    float r = this->r / 255.0f;
    float g = this->g / 255.0f;
    float b = this->b / 255.0f;

    float h, s, v; // h:0-360.0, s:0.0-1.0, v:0.0-1.0

    float max = r;
    if (g > max) max = g;
    if (b > max) max = b;

    float min = r;
    if (g < min) min = g;
    if (b < min) min = b;

    v = max;

    if (max == 0.0f) {
        s = 0;
        h = 0;
    }
    else if (max - min == 0.0f) {
        s = 0;
        h = 0;
    }
    else {
        s = (max - min) / max;

        if (max == r) {
            h = 60 * ((g - b) / (max - min)) + 0;
        }
        else if (max == g) {
            h = 60 * ((b - r) / (max - min)) + 120;
        }
        else {
            h = 60 * ((r - g) / (max - min)) + 240;
        }
    }

    if (h < 0) h += 360.0f;

    
    // dst_h = (uint16_t)(h / 2);   // dst_h : 0-180
    // dst_s = (uint8_t)(s * 255); // dst_s : 0-255
    // dst_v = (uint8_t)(v * 255); // dst_v : 0-255

    HSV hsv((uint16_t)(h), (uint8_t)(s * 255), (uint8_t)(v * 255));
    return hsv;
}