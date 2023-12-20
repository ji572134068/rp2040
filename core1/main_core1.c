#include "system.h"
#include "reset.h"
#include "clock.h"
#include "sio.h"
#include "gpio.h"
#include "RP2040.h"

void main_core1(void)
{
    gpio_set(21);
    gpio_clear(21);
}
