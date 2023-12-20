#include "system.h"
#include "reset.h"
#include "clock.h"
#include "sio.h"
#include "gpio.h"
#include "RP2040.h"
#include "main_core0.h"
#include "main_core1.h"

struct gpio_cfg_s gpio_led_cfg = {
    .pin = 25,
    .sio_dir = GPIO_SIO_DIR_OUT,
    .funcsel = GPIO_FUNC_SIO,
    .over_out = GPIO_OVER_OUT_PERIPHERAL,
    .over_oe = GPIO_OVER_OE_PERIPHERAL,
    .over_in = GPIO_OVER_IN_PERIPHERAL,
    .over_irq = GPIO_OVER_IRQ_NORMAL,
    .slew_rate = GPIO_PADS_SLEW_RATE_SLOW, /* slew rate control, slow or fast */
    .schmitt = ENABLE,                     /* enable or disable schmitt */
    .pull_down = DISABLE,                  /* enable or disable pull down */
    .pull_up = DISABLE,                    /* enable or disable pull up */
    .drive = GPIO_PADS_DRIVE_STRENGTH_4MA, /* drive strength */
    .ie = DISABLE,                         /* enable or disable input */
    .od = DISABLE,                         /* output disable, has priority over output enable from peripherals */
};

struct gpio_cfg_s gpio_clkout_cfg = {
    .pin = 21,
    .sio_dir = GPIO_SIO_DIR_IN,
    .funcsel = GPIO_FUNC_CLOCK,
    .over_out = GPIO_OVER_OUT_PERIPHERAL,
    .over_oe = GPIO_OVER_OE_PERIPHERAL,
    .over_in = GPIO_OVER_IN_PERIPHERAL,
    .over_irq = GPIO_OVER_IRQ_NORMAL,
    .slew_rate = GPIO_PADS_SLEW_RATE_SLOW, /* slew rate control, slow or fast */
    .schmitt = ENABLE,                     /* enable or disable schmitt */
    .pull_down = DISABLE,                  /* enable or disable pull down */
    .pull_up = DISABLE,                    /* enable or disable pull up */
    .drive = GPIO_PADS_DRIVE_STRENGTH_4MA, /* drive strength */
    .ie = DISABLE,                         /* enable or disable input */
    .od = DISABLE,                         /* output disable, has priority over output enable from peripherals */
};

void main_core1(void)
{
    volatile uint32_t *addr = (volatile uint32_t *)0xE000E018;

    __disable_irq();
    SysTick_Config(400 * 10);
    gpio_init(&gpio_clkout_cfg);
    clock_gpout_set(0, ENABLE, CLOCK_GPOUT0_SRC_SYS, 40 << 8, DISABLE, 0, 0);
    // while (*addr > 10 * 100) {}
    gpio_led_cfg.pin = gpio_clkout_cfg.pin;
    gpio_init(&gpio_led_cfg);
    gpio_led_cfg.pin = 25;
    main_core0();
    main_core1();
    while (1) {
        if (*addr < 100 * 10) {
            gpio_set(21);
        } else {
            gpio_clear(21);
        }
    }
}

extern uint32_t _vector;
extern uint32_t _stack_top_core1;
int main(void)
{
    reset_disable(RESET_IO_BANK0 | RESET_PADS_BANK0);
    gpio_init(&gpio_led_cfg);

    system_reset(SYSTEM_BLOCK_PROC1);
    sio_launch_core1(main_core1,&_stack_top_core1, _vector);

    __enable_irq();

    while (1) {
        static uint32_t tick_cnt = 0;
        if (tick_1ms > (tick_cnt + 200)) {
            tick_cnt = tick_1ms;
            gpio_toggle(gpio_led_cfg.pin);
        }
    }

    return 0;
}
