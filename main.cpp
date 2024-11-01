#include "pico/stdlib.h"
#include "pico/multicore.h"

#include "net/LEDModel.h"
#include "net/PioProvider.h"

#include "Serpentine.h"
#include "imgs.h"
#include "effects.h"

using namespace NetDriver;


void second_loop();

constexpr auto options = SingleLEDModel<WS2812b_2017>(2);
constexpr const uint8_t pins[] = {16,19};
auto provider = PIOProvider<SingleLEDModel<WS2812b_2017>, options>::getInstance(pins);
auto net = provider.getSender(0);
auto led = provider.getSender(1);


int main()
{
    multicore_launch_core1(second_loop);
    sleep_ms(2000);

    RGB pixel(0x0f, 0x02, 0x19);
    led.send(&pixel, 1);

    Serpentine::send(net, Colyber);
    sleep_ms(5000);

    while(1)
    {
        flyingParrot(net);
        // squareRainbow(net);
    }
    return 0;
}

void second_loop()
{
    gpio_init(25);
    gpio_set_dir(25, 1);
    while(1)
    {
        sleep_ms(500);
        gpio_put(25, 1);
        sleep_ms(500);
        gpio_put(25, 0);
    }
};
