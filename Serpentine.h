#pragma once

#include "net/ISender.h"

using namespace NetDriver;

class Serpentine
{
    public:
    static void send(const ISender& sender, RGB *data)
    {
        RGB data2[256];
        uint8_t idx=0;

        for (uint8_t i=8; i>0; --i)
        {
            for (uint8_t j=0; j<16; ++j)
                data2[idx++] = data[i*32-1 - j];
            for (uint8_t j=0; j<16; ++j)
                data2[idx++] = data[i*32-32 + j];
        }

        sender.send(data2, 256);
    }
};
