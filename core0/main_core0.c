#include "system.h"
#include "reset.h"
#include "clock.h"
#include "sio.h"
#include "gpio.h"
#include "RP2040.h"

void main_core0(void)
{
    gpio_clear(21);
    gpio_set(21);
}
