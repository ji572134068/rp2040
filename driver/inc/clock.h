#ifndef __HARDWARE_CLOCK_H__
#define __HARDWARE_CLOCK_H__

#include "reg.h"
#include "clock_reg.h"

#define CLOCK_ROSC_FREQ_RANGE_LOW     (0)
#define CLOCK_ROSC_FREQ_RANGE_MEDIUM  (1)
#define CLOCK_ROSC_FREQ_RANGE_HIGH    (2)
#define CLOCK_ROSC_FREQ_RANGE_TOOHIGH (3)
#define CLOCK_ROSC_FREQ_RANGE_INVALID (4)

#define CLOCK_ROSC_STATUS_ENABLED     (12)
#define CLOCK_ROSC_STATUS_DIV_RUNNING (16)
#define CLOCK_ROSC_STATUS_BADWRITE    (24)
#define CLOCK_ROSC_STATUS_STABLE      (31)

#define CLOCK_XOSC_STATUS_ENABLED     (12)
#define CLOCK_XOSC_STATUS_BADWRITE    (24)
#define CLOCK_XOSC_STATUS_STABLE      (31)

/* PLL type */
#define CLOCK_PLL_SYSPLL (0)
#define CLOCK_PLL_USBPLL (1)

/* clock instance */
#define CLOCK_GPOUT0 (0)
#define CLOCK_GPOUT1 (1)
#define CLOCK_GPOUT2 (2)
#define CLOCK_GPOUT3 (3)
#define CLOCK_REF    (4)
#define CLOCK_SYS    (5)
#define CLOCK_PERI   (6)
#define CLOCK_USB    (7)
#define CLOCK_ADC    (8)
#define CLOCK_RTC    (9)

/* clock source */
#define CLOCK_GPOUT0_SRC_SYSPLL (0)
#define CLOCK_GPOUT0_SRC_GPIN0  (1)
#define CLOCK_GPOUT0_SRC_GPIN1  (2)
#define CLOCK_GPOUT0_SRC_USBPLL (3)
#define CLOCK_GPOUT0_SRC_ROSC   (4)
#define CLOCK_GPOUT0_SRC_XOSC   (5)
#define CLOCK_GPOUT0_SRC_SYS    (6)
#define CLOCK_GPOUT0_SRC_USB    (7)
#define CLOCK_GPOUT0_SRC_ADC    (8)
#define CLOCK_GPOUT0_SRC_RTC    (9)
#define CLOCK_GPOUT0_SRC_REF    (10)

#define CLOCK_GPOUT1_SRC_SYSPLL (0)
#define CLOCK_GPOUT1_SRC_GPIN0  (1)
#define CLOCK_GPOUT1_SRC_GPIN1  (2)
#define CLOCK_GPOUT1_SRC_USBPLL (3)
#define CLOCK_GPOUT1_SRC_ROSC   (4)
#define CLOCK_GPOUT1_SRC_XOSC   (5)
#define CLOCK_GPOUT1_SRC_SYS    (6)
#define CLOCK_GPOUT1_SRC_USB    (7)
#define CLOCK_GPOUT1_SRC_ADC    (8)
#define CLOCK_GPOUT1_SRC_RTC    (9)
#define CLOCK_GPOUT1_SRC_REF    (10)

#define CLOCK_GPOUT2_SRC_SYSPLL  (0)
#define CLOCK_GPOUT2_SRC_GPIN0   (1)
#define CLOCK_GPOUT2_SRC_GPIN1   (2)
#define CLOCK_GPOUT2_SRC_USBPLL  (3)
#define CLOCK_GPOUT2_SRC_ROSC_PH (4)
#define CLOCK_GPOUT2_SRC_XOSC    (5)
#define CLOCK_GPOUT2_SRC_SYS     (6)
#define CLOCK_GPOUT2_SRC_USB     (7)
#define CLOCK_GPOUT2_SRC_ADC     (8)
#define CLOCK_GPOUT2_SRC_RTC     (9)
#define CLOCK_GPOUT2_SRC_REF     (10)

#define CLOCK_GPOUT3_SRC_SYSPLL  (0)
#define CLOCK_GPOUT3_SRC_GPIN0   (1)
#define CLOCK_GPOUT3_SRC_GPIN1   (2)
#define CLOCK_GPOUT3_SRC_USBPLL  (3)
#define CLOCK_GPOUT3_SRC_ROSC_PH (4)
#define CLOCK_GPOUT3_SRC_XOSC    (5)
#define CLOCK_GPOUT3_SRC_SYS     (6)
#define CLOCK_GPOUT3_SRC_USB     (7)
#define CLOCK_GPOUT3_SRC_ADC     (8)
#define CLOCK_GPOUT3_SRC_RTC     (9)
#define CLOCK_GPOUT3_SRC_REF     (10)

#define CLOCK_REF_SRC_USBPLL             (0)
#define CLOCK_REF_SRC_GPIN0              (1)
#define CLOCK_REF_SRC_GPIN1              (2)
#define CLOCK_REF_SRC_ROSC_PH_GLITCHLESS (3)
#define CLOCK_REF_SRC_XOSC_GLITCHLESS    (4)

#define CLOCK_SYS_SRC_SYSPLL         (0)
#define CLOCK_SYS_SRC_USBPLL         (1)
#define CLOCK_SYS_SRC_ROSC           (2)
#define CLOCK_SYS_SRC_XOSC           (3)
#define CLOCK_SYS_SRC_GPIN0          (4)
#define CLOCK_SYS_SRC_GPIN1          (5)
#define CLOCK_SYS_SRC_REF_GLITCHLESS (6)

#define CLOCK_PERI_SRC_SYS     (0)
#define CLOCK_PERI_SRC_SYSPLL  (1)
#define CLOCK_PERI_SRC_USBPLL  (2)
#define CLOCK_PERI_SRC_ROSC_PH (3)
#define CLOCK_PERI_SRC_XOSC    (4)
#define CLOCK_PERI_SRC_GPIN0   (5)
#define CLOCK_PERI_SRC_GPIN1   (6)

#define CLOCK_USB_SRC_USBPLL  (0)
#define CLOCK_USB_SRC_SYSPLL  (1)
#define CLOCK_USB_SRC_ROSC_PH (2)
#define CLOCK_USB_SRC_XOSC    (3)
#define CLOCK_USB_SRC_GPIN0   (4)
#define CLOCK_USB_SRC_GPIN1   (5)

#define CLOCK_ADC_SRC_USBPLL  (0)
#define CLOCK_ADC_SRC_SYSPLL  (1)
#define CLOCK_ADC_SRC_ROSC_PH (2)
#define CLOCK_ADC_SRC_XOSC    (3)
#define CLOCK_ADC_SRC_GPIN0   (4)
#define CLOCK_ADC_SRC_GPIN1   (5)

#define CLOCK_RTC_SRC_USBPLL  (0)
#define CLOCK_RTC_SRC_SYSPLL  (1)
#define CLOCK_RTC_SRC_ROSC_PH (2)
#define CLOCK_RTC_SRC_XOSC    (3)
#define CLOCK_RTC_SRC_GPIN0   (4)
#define CLOCK_RTC_SRC_GPIN1   (5)

#ifdef __cplusplus
extern "C" {
#endif

/* ROSC function */
void clock_rosc_enable(void);
void clock_rosc_disable(void);
void clock_rosc_set_freq_range(uint8_t freq_range);
uint8_t clock_rosc_get_freq_range(void);
void clock_rosc_set_strength(uint8_t stage, uint8_t strength);
uint8_t clock_rosc_get_strength(uint8_t stage);
void clock_rosc_dormant(void);
void clock_rosc_wake(void);
void clock_rosc_set_div(uint8_t div);
uint8_t clock_rosc_get_div(void);
uint8_t clock_rosc_get_status(uint8_t item);
void clock_rosc_clr_badwrite_status(void);
uint8_t clock_rosc_get_randombit(void);
void clock_rosc_set_count(uint8_t count);
uint8_t clock_rosc_get_count(void);

/* XOSC function */
void clock_xosc_enable(void);
void clock_xosc_disable(void);
uint8_t clock_xosc_get_status(uint8_t item);
void clock_xosc_clr_badwrite_status(void);
void clock_xosc_dormant(void);
void clock_xosc_wake(void);
void clock_xosc_set_startup_delay(uint32_t cycle);
void clock_xosc_set_count(uint8_t count);
uint8_t clock_xosc_get_count(void);

/* PLL function */
void clock_pll_init(uint8_t pll, uint8_t refdiv, uint8_t fbdiv, uint8_t postdiv1, uint8_t postdiv2);
void clock_pll_deinit(uint8_t pll);

/* CLOCK function */
void clock_gpout_set(uint8_t id, uint8_t enable, uint8_t src, uint32_t div, uint8_t dc50, uint8_t phase, uint8_t nudge);
uint32_t clock_ref_get_selected(void);
void clock_ref_set_src(uint8_t src);
void clock_ref_set_div(uint32_t div);
uint32_t clock_sys_get_selected(void);
void clock_sys_set_src(uint8_t src);
void clock_sys_set_div(uint32_t div);
void clock_peri_set(uint8_t enable, uint8_t src);
void clock_usb_set(uint8_t enable, uint8_t src, uint32_t div, uint8_t phase, uint8_t nudge);
void clock_adc_set(uint8_t enable, uint8_t src, uint32_t div, uint8_t phase, uint8_t nudge);
void clock_rtc_set(uint8_t enable, uint8_t src, uint32_t div, uint8_t phase, uint8_t nudge);
void clock_enable(uint8_t clock);
void clock_disable(uint8_t clock);
void clock_kill(uint8_t clock);

#ifdef __cplusplus
}
#endif

#endif /* __HARDWARE_CLOCK_H__ */
