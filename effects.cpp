#include "effects.h"

void flyingParrot(const ISender& net, bool rainbow)
{
    RGB buff[256];
    uint16_t hue=0;

    for (uint i=0; i<16; ++i)
    {
        for (uint j=0; j<16; ++j)
        for (uint k=0; k<16; ++k)
        {
            if (k + i < 16) buff[j*16 + k] = RGB();
            else
            {
                HSV hsv = FlyingBird[256*((i+3)%6) + j*16 + k - 16 + i].toHSV();
                hsv.h = (hsv.h + hue) %360;
                buff[j*16 + k] = hsv.toRGB();
            }
        }
        Serpentine::send(net, buff);
        if(rainbow) hue = (++hue)%360;
        sleep_ms(90);
    }
    for (uint i=0; i<16; ++i)
    {
        for (uint j=0; j<16; ++j)
        for (uint k=0; k<16; ++k)
        {
            if (k + i < 16)
            {
                HSV hsv = FlyingBird[256*((i)%6) + j*16 + k + i].toHSV();
                hsv.h = (hsv.h + hue) %360;
                buff[j*16 + k] = hsv.toRGB();
            } 
            else buff[j*16 + k] = RGB();
        }
        Serpentine::send(net, buff);
        if(rainbow) hue = (++hue)%360;
        sleep_ms(90);
    }
};

void squareRainbow(const ISender& net)
{
    RGB rgbb[256];
    for (uint i=0; i<360; ++i)
    {
        for (uint j=0; j<256; ++j)
            rgbb[j] = HSV((i + 2*j) % 360, 100, 3).toRGB();
        Serpentine::send(net, rgbb);
        sleep_ms(20);
    }
};
