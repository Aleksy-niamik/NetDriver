#pragma once

#include "pico/types.h"
#include "hardware/pio.h"
#include "WS2812b_2017.pio.h"

namespace NetDriver
{
    typedef void (*pio_program_init_t) (PIO pio, uint sm, uint offset, uint pin, float freq, uint bits);

    struct LEDModel
    {
        uint TL0, TL1, TH0, TH1;    // in ns
        uint reset;                 // in us
        float frequency;            // in Hz, frequency of transmitting one bit

        const pio_program_t *program;
        const pio_program_init_t program_init;

        constexpr LEDModel(uint tl0, uint tl1, uint th0, uint th1, uint res, float freq,
             const pio_program_t *_program, const pio_program_init_t _program_init)
        : TL0(tl0), TL1(tl1), TH0(th0), TH1(th1), reset(res), frequency(freq),
          program(_program), program_init(_program_init)
        {
        }
    };

    constexpr LEDModel WS2812b_2017 = LEDModel(900,350,350,900,280, 800000, 
        &ws2812b_2017_program, &ws2812b_2017_program_init);
}
