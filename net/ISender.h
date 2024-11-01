#pragma once

#include "pico/types.h"

#include "LEDModel.h"
#include "ColorSpaces.h"

namespace NetDriver
{
    class ISender
    {
    public:
        virtual ~ISender() {}

        virtual void send(const RGB* data, size_t len) const = 0;
    };
};