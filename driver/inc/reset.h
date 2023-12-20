#ifndef __HARDWARE_RESET_H__
#define __HARDWARE_RESET_H__

#include "reg.h"
#include "reset_reg.h"

#define RESET_ADC        (1 << 0)
#define RESET_BUSCTRL    (1 << 1)
#define RESET_DMA        (1 << 2)
#define RESET_I2C0       (1 << 3)
#define RESET_I2C1       (1 << 4)
#define RESET_IO_BANK0   (1 << 5)
#define RESET_IO_QSPI    (1 << 6)
#define RESET_JTAG       (1 << 7)
#define RESET_PADS_BANK0 (1 << 8)
#define RESET_PADS_QSPI  (1 << 9)
#define RESET_PIO0       (1 << 10)
#define RESET_PIO1       (1 << 11)
#define RESET_SYSPLL     (1 << 12)
#define RESET_USBPLL     (1 << 13)
#define RESET_PWM        (1 << 14)
#define RESET_RTC        (1 << 15)
#define RESET_SPI0       (1 << 16)
#define RESET_SPI1       (1 << 17)
#define RESET_SYSCFG     (1 << 18)
#define RESET_SYSINFO    (1 << 19)
#define RESET_TBMAN      (1 << 20)
#define RESET_TIMER      (1 << 21)
#define RESET_UART0      (1 << 22)
#define RESET_UART1      (1 << 23)
#define RESET_USBCTRL    (1 << 24)
#define RESET_ALL        ((1 << 25) - 1)

#ifdef __cplusplus
extern "C" {
#endif

void reset_enable(uint32_t reset);
void reset_disable(uint32_t reset);
void reset(uint32_t reset);
uint32_t reset_get_state(uint32_t reset);
void reset_wdg_bound(uint32_t reset);
void reset_wdg_unbound(uint32_t reset);
uint32_t reset_get_wdg_bound_state(uint32_t reset);

#ifdef __cplusplus
}
#endif

#endif /* __HARDWARE_RESET_H__ */
