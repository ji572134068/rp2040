#ifndef __HARDWARE_CLOCK_REG_H__
#define __HARDWARE_CLOCK_REG_H__

/* ROSC_BASE @0x40060000 */
#define CLOCK_ROSC_CTRL_OFFSET      (0x000)
#define CLOCK_ROSC_FREQA_OFFSET     (0x004)
#define CLOCK_ROSC_FREQB_OFFSET     (0x008)
#define CLOCK_ROSC_DORMANT_OFFSET   (0x00C)
#define CLOCK_ROSC_DIV_OFFSET       (0x010)
#define CLOCK_ROSC_PHASE_OFFSET     (0x014)
#define CLOCK_ROSC_STATUS_OFFSET    (0x018)
#define CLOCK_ROSC_RANDOMBIT_OFFSET (0x01C)
#define CLOCK_ROSC_COUNT_OFFSET     (0x020)

/* XOSC_BASE @0x40024000 */
#define CLOCK_XOSC_CTRL_OFFSET      (0x000)
#define CLOCK_XOSC_STATUS_OFFSET    (0x004)
#define CLOCK_XOSC_DORMANT_OFFSET   (0x008)
#define CLOCK_XOSC_STARTUP_OFFSET   (0x00C)
#define CLOCK_XOSC_COUNT_OFFSET     (0x01C)

/* PLL_SYS_BASE @0x40028000 */
/* PLL_USB_BASE @0x4002C000 */
#define CLOCK_PLL_CS_OFFSET        (0x000)
#define CLOCK_PLL_PWR_OFFSET       (0x004)
#define CLOCK_PLL_FBDIV_INT_OFFSET (0x008)
#define CLOCK_PLL_PRIM_OFFSET      (0x00C)

/* CLOCKS_BASE @0x40008000 */
#define CLOCK_CTRL_OFFSET            (0x000)
#define CLOCK_DIV_OFFSET             (0x004)
#define CLOCK_SELECTED_OFFSET        (0x008)
#define CLOCK_GPOUT0_CTRL_OFFSET     (0x000)
#define CLOCK_GPOUT0_DIV_OFFSET      (0x004)
#define CLOCK_GPOUT0_SELECTED_OFFSET (0x008)
#define CLOCK_GPOUT1_CTRL_OFFSET     (0x00C)
#define CLOCK_GPOUT1_DIV_OFFSET      (0x010)
#define CLOCK_GPOUT1_SELECTED_OFFSET (0x014)
#define CLOCK_GPOUT2_CTRL_OFFSET     (0x018)
#define CLOCK_GPOUT2_DIV_OFFSET      (0x01C)
#define CLOCK_GPOUT2_SELECTED_OFFSET (0x020)
#define CLOCK_GPOUT3_CTRL_OFFSET     (0x024)
#define CLOCK_GPOUT3_DIV_OFFSET      (0x028)
#define CLOCK_GPOUT3_SELECTED_OFFSET (0x02C)
#define CLOCK_REF_CTRL_OFFSET        (0x030)
#define CLOCK_REF_DIV_OFFSET         (0x034)
#define CLOCK_REF_SELECTED_OFFSET    (0x038)
#define CLOCK_SYS_CTRL_OFFSET        (0x03C)
#define CLOCK_SYS_DIV_OFFSET         (0x040)
#define CLOCK_SYS_SELECTED_OFFSET    (0x044)
#define CLOCK_PERI_CTRL_OFFSET       (0x048)
#define CLOCK_PERI_DIV_OFFSET        (0x04C)
#define CLOCK_PERI_SELECTED_OFFSET   (0x050)
#define CLOCK_USB_CTRL_OFFSET        (0x054)
#define CLOCK_USB_DIV_OFFSET         (0x058)
#define CLOCK_USB_SELECTED_OFFSET    (0x05C)
#define CLOCK_ADC_CTRL_OFFSET        (0x060)
#define CLOCK_ADC_DIV_OFFSET         (0x064)
#define CLOCK_ADC_SELECTED_OFFSET    (0x068)
#define CLOCK_RTC_CTRL_OFFSET        (0x06C)
#define CLOCK_RTC_DIV_OFFSET         (0x070)
#define CLOCK_RTC_SELECTED_OFFSET    (0x074)

/* CLOCK_ROSC_CTRL_OFFSET */
#define CLOCK_ROSC_FREQ_RANGE_POS  (0)
#define CLOCK_ROSC_FREQ_RANGE_MASK (0xFFF)
#define CLOCK_ROSC_ENABLE_POS      (12)
#define CLOCK_ROSC_ENABLE_MASK     (0xFFF)

/* CLOCK_ROSC_FREQ_OFFSET */
#define CLOCK_ROSC_STRENGTH_MASK  (0x7)

/* CLOCK_XOSC_CTRL_OFFSET */
#define CLOCK_XOSC_FREQ_RANGE_POS  (0)
#define CLOCK_XOSC_FREQ_RANGE_MASK (0xFFF)
#define CLOCK_XOSC_ENABLE_POS      (12)
#define CLOCK_XOSC_ENABLE_MASK     (0xFFF)

/* CLOCK_XOSC_STARTUP_OFFSET */
#define CLOCK_XOSC_STARTUP_DELAY_POS  (0)
#define CLOCK_XOSC_STARTUP_DELAY_MASK (0x3FFF)
#define CLOCK_XOSC_STARTUP_X4_POS     (20)

/* CLOCK_PLL_CS_OFFSET */
#define CLOCK_PLL_REFDIV_POS  (0)
#define CLOCK_PLL_REFDIV_MASK (0x3F)
#define CLOCK_PLL_BYPASS_POS  (8)
#define CLOCK_PLL_LOCK_POS    (31)

/* CLOCK_PLL_PWR_OFFSET */
#define CLOCK_PLL_PD_POS        (0)
#define CLOCK_PLL_DSMPD_POS     (2)
#define CLOCK_PLL_POSTDIVPD_POS (3)
#define CLOCK_PLL_VCOPD_POS     (5)
#define CLOCK_PLL_PWR_MASK  ((1 << CLOCK_PLL_PD_POS)        | \
                             (1 << CLOCK_PLL_DSMPD_POS)     | \
                             (1 << CLOCK_PLL_POSTDIVPD_POS) | \
                             (1 << CLOCK_PLL_VCOPD_POS))
/* CLOCK_PLL_PRIM_OFFSET */
#define CLOCK_PLL_POSTDIV2_POS  (12)
#define CLOCK_PLL_POSTDIV2_MASK (0x7)
#define CLOCK_PLL_POSTDIV1_POS  (16)
#define CLOCK_PLL_POSTDIV1_MASK (0x7)

/* CLOCK_CTRL_OFFSET */
#define CLOCK_SRC_POS     (0)
#define CLOCK_SRC_MASK    (0x3)
#define CLOCK_AUXSRC_POS  (5)
#define CLOCK_AUXSRC_MASK (0xF)
#define CLOCK_KILL_POS    (10)
#define CLOCK_ENABLE_POS  (11)
#define CLOCK_DC50_POS    (12)
#define CLOCK_PHASE_POS   (16)
#define CLOCK_PHASE_MASK  (0x3)
#define CLOCK_NUDGE_POS   (20)

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* __HARDWARE_CLOCK_REG_H__ */
