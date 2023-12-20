#ifndef __HARDWARE_GPIO_H__
#define __HARDWARE_GPIO_H__

#include "reg.h"
#include "gpio_reg.h"
#include "sio_reg.h"

#define GPIO_SIO_DIR_IN                  (0)
#define GPIO_SIO_DIR_OUT                 (1)

#define GPIO_FUNC_XIP                    (0) /* not available for GPIO0~29 */
#define GPIO_FUNC_SPI                    (1) /* only available for GPIO0~29 */
#define GPIO_FUNC_UART                   (2) /* only available for GPIO0~29 */
#define GPIO_FUNC_I2C                    (3) /* only available for GPIO0~29 */
#define GPIO_FUNC_PWM                    (4) /* only available for GPIO0~29 */
#define GPIO_FUNC_SIO                    (5) /* available for all GPIO */
#define GPIO_FUNC_PIO0                   (6) /* only available for GPIO0~29 */
#define GPIO_FUNC_PIO1                   (7) /* only available for GPIO0~29 */
#define GPIO_FUNC_CLOCK                  (8) /* only available for GPIO20~25 */
#define GPIO_FUNC_USB                    (9)
#define GPIO_FUNC_NULL                   (31)

#define GPIO_IRQ_NULL                    (0)
#define GPIO_IRQ_LEVEL_LOW               (1)
#define GPIO_IRQ_LEVEL_HIGH              (2)
#define GPIO_IRQ_EDGE_FALL               (4)
#define GPIO_IRQ_EDGE_RISE               (8)

#define GPIO_OVER_OUT_PERIPHERAL         (0)
#define GPIO_OVER_OUT_PERIPHERAL_INVERSE (1)
#define GPIO_OVER_OUT_FORCE_LOW          (2)
#define GPIO_OVER_OUT_FORCE_HIGH         (3)

#define GPIO_OVER_OE_PERIPHERAL          (0)
#define GPIO_OVER_OE_PERIPHERAL_INVERSE  (1)
#define GPIO_OVER_OE_FORCE_DISABLE       (2)
#define GPIO_OVER_OE_FORCE_ENABLE        (3)

#define GPIO_OVER_IN_PERIPHERAL          (0)
#define GPIO_OVER_IN_PERIPHERAL_INVERSE  (1)
#define GPIO_OVER_IN_FORCE_LOW           (2)
#define GPIO_OVER_IN_FORCE_HIGH          (3)

#define GPIO_OVER_IRQ_NORMAL             (0)
#define GPIO_OVER_IRQ_INVERSE            (1)
#define GPIO_OVER_IRQ_FORCE_LOW          (2)
#define GPIO_OVER_IRQ_FORCE_HIGH         (3)

#define GPIO_PADS_VOLTAGE_3V3 (0)
#define GPIO_PADS_VOLTAGE_1V8 (1)

#define GPIO_PADS_DRIVE_STRENGTH_2MA  (0)
#define GPIO_PADS_DRIVE_STRENGTH_4MA  (1)
#define GPIO_PADS_DRIVE_STRENGTH_8MA  (2)
#define GPIO_PADS_DRIVE_STRENGTH_12MA (3)

#define GPIO_PADS_SLEW_RATE_SLOW (0)
#define GPIO_PADS_SLEW_RATE_FAST (1)

struct gpio_cfg_s {
    uint8_t pin;
    uint8_t sio_dir;   /* GPIO_SIO_DIR_XXX */
    uint8_t funcsel;   /* GPIO_FUNC_XXX */
    uint8_t over_out;  /* GPIO_OVER_OUT_XXX */
    uint8_t over_oe;   /* GPIO_OVER_OE_XXX */
    uint8_t over_in;   /* GPIO_OVER_IN_XXX */
    uint8_t over_irq;  /* GPIO_OVER_IRQ_XXX */
    uint8_t slew_rate; /* slew rate control, slow or fast */
    uint8_t schmitt;   /* enable or disable schmitt */
    uint8_t pull_down; /* enable or disable pull down */
    uint8_t pull_up;   /* enable or disable pull up */
    uint8_t drive;     /* drive strength */
    uint8_t ie;        /* enable or disable input */
    uint8_t od;        /* output disable, has priority over output enable from peripherals */
};

#ifdef __cplusplus
extern "C" {
#endif

uint8_t gpio_read(uint8_t pin);
void gpio_write(uint8_t pin, uint8_t value);
void gpio_set(uint8_t pin);
void gpio_clear(uint8_t pin);
void gpio_toggle(uint8_t pin);
void gpio_oe_write(uint8_t pin, uint8_t value);
void gpio_oe_set(uint8_t pin);
void gpio_oe_clear(uint8_t pin);
void gpio_oe_toggle(uint8_t pin);

uint32_t gpio_read_multi(void);
void gpio_write_multi(uint32_t value);
void gpio_set_multi(uint32_t pins);
void gpio_clear_multi(uint32_t pins);
void gpio_toggle_multi(uint32_t pins);
void gpio_oe_write_multi(uint32_t value);
void gpio_oe_set_multi(uint32_t pins);
void gpio_oe_clear_multi(uint32_t pins);
void gpio_oe_toggle_multi(uint32_t pins);

uint32_t gpio_get_status(uint8_t pin, uint32_t status);
void gpio_func_sel(uint8_t pin, uint8_t func);
void gpio_over_out_set(uint8_t pin, uint8_t over);
void gpio_over_oe_set(uint8_t pin, uint8_t over);
void gpio_over_in_set(uint8_t pin, uint8_t over);
void gpio_over_irq_set(uint8_t pin, uint8_t over);

void gpio_init(struct gpio_cfg_s *cfg);

uint8_t gpio_irq_get_raw_status(uint8_t pin, uint8_t irq);
void gpio_irq_raw_status_clear(uint8_t pin, uint8_t irq);
void gpio_irq_enable_proc0(uint8_t pin, uint8_t irq);
void gpio_irq_disable_proc0(uint8_t pin, uint8_t irq);
void gpio_irq_force_proc0(uint8_t pin, uint8_t irq);
void gpio_irq_deforce_proc0(uint8_t pin, uint8_t irq);
uint8_t gpio_irq_get_status_proc0(uint8_t pin, uint8_t irq);
void gpio_irq_enable_proc1(uint8_t pin, uint8_t irq);
void gpio_irq_disable_proc1(uint8_t pin, uint8_t irq);
void gpio_irq_force_proc1(uint8_t pin, uint8_t irq);
void gpio_irq_deforce_proc1(uint8_t pin, uint8_t irq);
uint8_t gpio_irq_get_status_proc1(uint8_t pin, uint8_t irq);
void gpio_irq_enable_dormant(uint8_t pin, uint8_t irq);
void gpio_irq_disable_dormant(uint8_t pin, uint8_t irq);
void gpio_irq_force_dormant(uint8_t pin, uint8_t irq);
void gpio_irq_deforce_dormant(uint8_t pin, uint8_t irq);
uint8_t gpio_irq_get_status_dormant(uint8_t pin, uint8_t irq);

#ifdef __cplusplus
}
#endif

#endif /* __HARDWARE_GPIO_H__ */
