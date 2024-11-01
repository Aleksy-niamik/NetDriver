#pragma once

#include "pico/types.h"

#include "LEDModel.h"
#include "ISender.h"
#include "ColorSpaces.h"

namespace NetDriver
{ 
    template <typename T, const T& options>
    class PIOProvider
    {
    };

    template <const LEDModel& model>
    class SingleLEDModel
    {
        public:
        const uint8_t numberOfSenders;

        public:
        constexpr SingleLEDModel(uint8_t noSenders)
        : numberOfSenders(noSenders)
        {
        }

    };

    template <const LEDModel& ledModel, const SingleLEDModel<ledModel>& options>
    class PIOProvider<SingleLEDModel<ledModel>, options>
    {
        class PIOSender : public ISender
        {
            private:
            PIO _pio;
            uint _sm;
            PIOSender() {}
            PIOSender(PIO pio, uint sm, uint offset, uint pin)
            : _pio(pio), _sm(sm)
            {
                ledModel.program_init(pio, sm, offset, pin, ledModel.frequency, 24);
            }

            public:
            friend class PIOProvider;

            void send(const RGB *data, size_t len) const override
            {
                for (uint i=0; i<len; ++i)
                {
                    RGB rgb = data[i];
                    pio_sm_put_blocking(_pio, _sm, rgb.g << 24 | rgb.r << 16 | rgb.b << 8);
                }
            };
        };

        private:
        PIOSender senders[options.numberOfSenders];
        uint8_t pins[options.numberOfSenders];

        PIOProvider(const uint8_t _pins[])
        {
            static_assert(options.numberOfSenders > 0 && options.numberOfSenders < 9, "number of senders cannot be greater than 8 and less than 1");

            for(int i=0; i< options.numberOfSenders; i++)
                pins[i] = _pins[i];
            if(options.numberOfSenders < 5)
            {
                uint offset = pio_add_program(pio0, ledModel.program);
                for(int i=0; i<options.numberOfSenders; i++)
                    senders[i] = PIOSender(pio0, i, offset, pins[i]);
            }
            else
            {
                uint offset0 = pio_add_program(pio0, ledModel.program);
                uint offset1 = pio_add_program(pio1, ledModel.program);
                for(int i=0; i<4; i++)
                    senders[i] = PIOSender(pio0, i, offset0, pins[i]);
                for(int i=4; i<options.numberOfSenders; i++)
                    senders[i] = PIOSender(pio1, i-4, offset1, pins[i]);
            }
        }

        public:
        static const PIOProvider& getInstance(const uint8_t _pins[])
        {
            static PIOProvider provider(_pins);
            return provider;
        } 

        const PIOSender& getSender(uint8_t nr) const
        {
            if (nr < options.numberOfSenders)
                return senders[nr];
        }
    };
}
