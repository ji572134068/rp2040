#include "clock.h"
#include "reset.h"

void clock_rosc_enable(void)
{
    uint32_t addr;
    uint32_t val;

    if (clock_rosc_get_status(CLOCK_ROSC_STATUS_STABLE)) {
        return;
    }
    addr = ROSC_BASE + CLOCK_ROSC_CTRL_OFFSET;
    val = getreg32(addr);
    val &= ~(CLOCK_ROSC_ENABLE_MASK << CLOCK_ROSC_ENABLE_POS);
    val |= (uint32_t)0xFAB << CLOCK_ROSC_ENABLE_POS;
    putreg32(val, addr);
    while (!clock_rosc_get_status(CLOCK_ROSC_STATUS_STABLE));
}

void clock_rosc_disable(void)
{
    uint32_t addr;
    uint32_t val;

    addr = ROSC_BASE + CLOCK_ROSC_CTRL_OFFSET;
    val = getreg32(addr);
    val &= ~(CLOCK_ROSC_ENABLE_MASK << CLOCK_ROSC_ENABLE_POS);
    val |= (uint32_t)0xD1E << CLOCK_ROSC_ENABLE_POS;
    putreg32(val, addr);
}

void clock_rosc_set_freq_range(uint8_t freq_range)
{
    uint32_t addr;
    uint32_t val;
    uint32_t magic;

    switch (freq_range) {
        case CLOCK_ROSC_FREQ_RANGE_LOW:
            magic = 0xFA4;
            break;
        case CLOCK_ROSC_FREQ_RANGE_MEDIUM:
            magic = 0xFA5;
            break;
        case CLOCK_ROSC_FREQ_RANGE_HIGH:
            magic = 0xFA7;
            break;
        case CLOCK_ROSC_FREQ_RANGE_TOOHIGH:
            magic = 0xFA6;
            break;
        default:
            magic = 0xFA4;
            break;
    }
    addr = ROSC_BASE + CLOCK_ROSC_CTRL_OFFSET;
    val = getreg32(addr);
    val &= ~(CLOCK_ROSC_FREQ_RANGE_MASK << CLOCK_ROSC_FREQ_RANGE_POS);
    val |= magic << CLOCK_ROSC_FREQ_RANGE_POS;
    putreg32(val, addr);
}

uint8_t clock_rosc_get_freq_range(void)
{
    uint32_t addr;
    uint32_t val;
    uint8_t freq_range;

    addr = ROSC_BASE + CLOCK_ROSC_CTRL_OFFSET;
    val = getreg32(addr);
    val >>= CLOCK_ROSC_FREQ_RANGE_POS;
    val &= CLOCK_ROSC_FREQ_RANGE_MASK;
    switch (val) {
        case 0xFA4:
            freq_range = CLOCK_ROSC_FREQ_RANGE_LOW;
            break;
        case 0xFA5:
            freq_range = CLOCK_ROSC_FREQ_RANGE_MEDIUM;
            break;
        case 0xFA7:
            freq_range = CLOCK_ROSC_FREQ_RANGE_HIGH;
            break;
        case 0xFA6:
            freq_range = CLOCK_ROSC_FREQ_RANGE_TOOHIGH;
            break;
        default:
            freq_range = CLOCK_ROSC_FREQ_RANGE_INVALID;
            break;
    }
    return freq_range;
}

void clock_rosc_set_strength(uint8_t stage, uint8_t strength)
{
    uint32_t addr;
    uint32_t val;
    uint8_t pos;

    if (stage < 4) {
        addr = ROSC_BASE + CLOCK_ROSC_FREQA_OFFSET;
    } else {
        addr = ROSC_BASE + CLOCK_ROSC_FREQB_OFFSET;
    }
    pos = (stage & 0x03) << 2;
    val = getreg32(addr);
    val &= ~(CLOCK_ROSC_STRENGTH_MASK << pos);
    val |= strength << pos;
    putreg32(val, addr);
}

uint8_t clock_rosc_get_strength(uint8_t stage)
{
    uint32_t addr;
    uint32_t val;
    uint8_t pos;

    if (stage < 4) {
        addr = ROSC_BASE + CLOCK_ROSC_FREQA_OFFSET;
    } else {
        addr = ROSC_BASE + CLOCK_ROSC_FREQB_OFFSET;
    }
    pos = (stage & 0x03) << 2;
    val = getreg32(addr);
    val >>= pos;
    val &= CLOCK_ROSC_STRENGTH_MASK;
    return (uint8_t)val;
}

void clock_rosc_dormant(void)
{
    putreg32(0x636F6D61, ROSC_BASE + CLOCK_ROSC_DORMANT_OFFSET);
}

void clock_rosc_wake(void)
{
    putreg32(0x77616B65, ROSC_BASE + CLOCK_ROSC_DORMANT_OFFSET);
}

void clock_rosc_set_div(uint8_t div)
{
    uint32_t val;

    div &= 0x1F;
    val = 0xAA0 + (uint32_t)div;
    putreg32(val, ROSC_BASE + CLOCK_ROSC_DIV_OFFSET);
}

uint8_t clock_rosc_get_div(void)
{
    uint32_t val;

    val = getreg32(ROSC_BASE + CLOCK_ROSC_DIV_OFFSET);
    val -= 0xAA0;
    return (uint8_t)val;
}

uint8_t clock_rosc_get_status(uint8_t item)
{
    uint32_t val;

    val = getreg32(ROSC_BASE + CLOCK_ROSC_STATUS_OFFSET);
    val &= (1 << item);
    if (val) {
        return 1;
    } else {
        return 0;
    }
}

void clock_rosc_clr_badwrite_status(void)
{
    putreg32(1 << CLOCK_ROSC_STATUS_BADWRITE, ROSC_BASE + CLOCK_ROSC_STATUS_OFFSET);
}

uint8_t clock_rosc_get_randombit(void)
{
    uint32_t val;

    val = getreg32(ROSC_BASE + CLOCK_ROSC_RANDOMBIT_OFFSET);
    val &= 0x01;
    return (uint8_t)val;
}

void clock_rosc_set_count(uint8_t count)
{
    putreg32((uint32_t)count, ROSC_BASE + CLOCK_ROSC_COUNT_OFFSET);
}

uint8_t clock_rosc_get_count(void)
{
    return (uint8_t)getreg32(ROSC_BASE + CLOCK_ROSC_COUNT_OFFSET);
}

/************************* XOSC function *************************/
void clock_xosc_enable(void)
{
    uint32_t addr;
    uint32_t val;
    if (clock_xosc_get_status(CLOCK_XOSC_STATUS_STABLE)) {
        return;
    }
    addr = XOSC_BASE + CLOCK_XOSC_CTRL_OFFSET;
    val = getreg32(addr);
    val &= ~(CLOCK_XOSC_ENABLE_MASK << CLOCK_XOSC_ENABLE_POS);
    val |= (uint32_t)0xFAB << CLOCK_XOSC_ENABLE_POS;
    putreg32(val, addr);
    while (!clock_xosc_get_status(CLOCK_XOSC_STATUS_STABLE));
}

void clock_xosc_disable(void)
{
    uint32_t addr;
    uint32_t val;

    addr = XOSC_BASE + CLOCK_XOSC_CTRL_OFFSET;
    val = getreg32(addr);
    val &= ~(CLOCK_XOSC_ENABLE_MASK << CLOCK_XOSC_ENABLE_POS);
    val |= (uint32_t)0xD1E << CLOCK_XOSC_ENABLE_POS;
    putreg32(val, addr);
}

uint8_t clock_xosc_get_status(uint8_t item)
{
    uint32_t val;

    val = getreg32(XOSC_BASE + CLOCK_XOSC_STATUS_OFFSET);
    val &= (1 << item);
    if (val) {
        return 1;
    } else {
        return 0;
    }
}

void clock_xosc_clr_badwrite_status(void)
{
    putreg32(1 << CLOCK_XOSC_STATUS_BADWRITE, XOSC_BASE + CLOCK_XOSC_STATUS_OFFSET);
}

void clock_xosc_dormant(void)
{
    putreg32(0x636F6D61, XOSC_BASE + CLOCK_XOSC_DORMANT_OFFSET);
}

void clock_xosc_wake(void)
{
    putreg32(0x77616B65, XOSC_BASE + CLOCK_XOSC_DORMANT_OFFSET);
}

void clock_xosc_set_startup_delay(uint32_t cycle)
{
    uint32_t x4;
    uint32_t val;

    x4 = 0;
    cycle >>= 8; /* in multiples of 256*xtal_period */
    if (cycle > CLOCK_XOSC_STARTUP_DELAY_MASK) {
        x4 = 1;
        cycle >>= 2; /* multiplies the startup_delay by 4 */
        if (cycle > CLOCK_XOSC_STARTUP_DELAY_MASK) {
            cycle = CLOCK_XOSC_STARTUP_DELAY_MASK;
        }
    }
    val = ((x4 << CLOCK_XOSC_STARTUP_X4_POS) | (cycle << CLOCK_XOSC_STARTUP_DELAY_POS));
    putreg32(val, XOSC_BASE + CLOCK_XOSC_STARTUP_OFFSET);
}

void clock_xosc_set_count(uint8_t count)
{
    putreg32((uint32_t)count, XOSC_BASE + CLOCK_XOSC_COUNT_OFFSET);
}
uint8_t clock_xosc_get_count(void)
{
    return (uint8_t)getreg32(XOSC_BASE + CLOCK_XOSC_COUNT_OFFSET);
}

void clock_pll_init(uint8_t pll, uint8_t refdiv, uint8_t fbdiv, uint8_t postdiv1, uint8_t postdiv2)
{
    uint32_t addr;
    uint32_t val;

    if (pll == CLOCK_PLL_SYSPLL) {
        reset_enable(RESET_SYSPLL);
        reset_disable(RESET_SYSPLL);
        addr = PLL_SYS_BASE;
    } else if (pll == CLOCK_PLL_USBPLL) {
        reset_enable(RESET_USBPLL);
        reset_disable(RESET_USBPLL);
        addr = PLL_USB_BASE;
    } else {
        return;
    }
    /* Load VCO-related dividers before starting VCO */
    putreg32((uint32_t)refdiv, addr + CLOCK_PLL_CS_OFFSET);
    putreg32((uint32_t)fbdiv, addr + CLOCK_PLL_FBDIV_INT_OFFSET);
    /* Turn on PLL */
    val = (1 << CLOCK_PLL_PD_POS) | (1 << CLOCK_PLL_VCOPD_POS);
    putreg32(val, addr + CLOCK_PLL_PWR_OFFSET + REG_ALIAS_CLR_BITS);
    /* Wait for PLL to lock */
    while (1) {
        val = getreg32(addr + CLOCK_PLL_CS_OFFSET);
        val &= (1 << CLOCK_PLL_LOCK_POS);
        if (val) {
            break;
        }
    }
    /* Set up post dividers */
    val = (postdiv1 << CLOCK_PLL_POSTDIV1_POS) | (postdiv2 << CLOCK_PLL_POSTDIV2_POS);
    putreg32(val, addr + CLOCK_PLL_PRIM_OFFSET);
    /* Turn on post divider */
    putreg32(1 << CLOCK_PLL_POSTDIVPD_POS, addr + CLOCK_PLL_PWR_OFFSET + REG_ALIAS_CLR_BITS);
}

void clock_pll_deinit(uint8_t pll)
{
    if (pll == CLOCK_PLL_SYSPLL) {
        reset_enable(RESET_SYSPLL);
        reset_disable(RESET_SYSPLL);
        putreg32(CLOCK_PLL_PWR_MASK, PLL_SYS_BASE + CLOCK_PLL_PWR_OFFSET);
    } else if (pll == CLOCK_PLL_USBPLL) {
        reset_enable(RESET_USBPLL);
        reset_disable(RESET_USBPLL);
        putreg32(CLOCK_PLL_PWR_MASK, PLL_USB_BASE + CLOCK_PLL_PWR_OFFSET);
    }
}

/* id: 0 ~ 3 */
/* div[31:8]: Integer component of the divisor, 0 is for 2^24 */
/* div[ 7:0]: Fractional component of the divisor */
/* phase: 0 ~ 3 */
void clock_gpout_set(uint8_t id, uint8_t enable, uint8_t src, uint32_t div, uint8_t dc50, uint8_t phase, uint8_t nudge)
{
    uint32_t addr;
    uint32_t val;

    /* step1: disable clock */
    addr = CLOCKS_BASE + CLOCK_GPOUT0_CTRL_OFFSET + id * 0xC;
    putreg32(1 << CLOCK_ENABLE_POS, addr + REG_ALIAS_CLR_BITS);

    /* step2: config ctrl register */
    val = getreg32(addr);
    /* config clock source */
    val &= ~(CLOCK_AUXSRC_MASK << CLOCK_AUXSRC_POS);
    val |= ((src & CLOCK_AUXSRC_MASK) << CLOCK_AUXSRC_POS);
    /* config duty cycle correction for odd divisors */
    if (dc50) {
        val |= 1 << CLOCK_DC50_POS;
    } else {
        val &= ~(1 << CLOCK_DC50_POS);
    }
    /* config delay phase up to 3 cycles of the input clock */
    val &= ~(CLOCK_PHASE_MASK << CLOCK_PHASE_POS);
    val |= ((phase & CLOCK_PHASE_MASK) << CLOCK_PHASE_POS);
    /* config signal shifts the phase of the output by 1 cycle of the input clock */
    if (nudge) {
        val |= 1 << CLOCK_NUDGE_POS;
    } else {
        val &= ~(1 << CLOCK_NUDGE_POS);
    }
    /* disable clock */
    val &= ~(1 << CLOCK_ENABLE_POS);
    putreg32(val, addr);

    /* step3: config div */
    putreg32(div, CLOCKS_BASE + CLOCK_GPOUT0_DIV_OFFSET + id * 0xC);

    /* step4: config enable */
    if (enable) {
        putreg32(1 << CLOCK_ENABLE_POS, addr + REG_ALIAS_SET_BITS);
    }
}

uint32_t clock_ref_get_selected(void)
{
    return getreg32(CLOCKS_BASE + CLOCK_REF_SELECTED_OFFSET);
}

void clock_ref_set_src(uint8_t src)
{
    uint32_t addr;
    uint32_t val;

    addr = CLOCKS_BASE + CLOCK_REF_CTRL_OFFSET;
    if (src == CLOCK_REF_SRC_ROSC_PH_GLITCHLESS) {
        /* switch to the glitchless mux */
        clock_rosc_enable();
        /* step1: switch the glitchless mux to an alternate source */
        putreg32(0, addr);
        /* step2: poll the SELECTED register until the switch is completed */
        while (1) {
            if (clock_ref_get_selected() & (1 << 0)) {
                break;
            }
        }
    } else if (src == CLOCK_REF_SRC_XOSC_GLITCHLESS) {
        /* switch to the glitchless mux */
        clock_xosc_enable();
        /* step1: switch the glitchless mux to an alternate source */
        putreg32(2, addr);
        /* step2: poll the SELECTED register until the switch is completed */
        while (1) {
            if (clock_ref_get_selected() & (1 << 2)) {
                break;
            }
        }
    } else {
        /* switch to the auxiliary mux when the generator has a glitchless mux */
        clock_rosc_enable();
        /* step1: switch the glitchless mux to a source that isn’t the aux mux */
        putreg32(0, addr);
        /* step2: poll the SELECTED register until the switch is completed */
        while (1) {
            if (clock_ref_get_selected() & (1 << 0)) {
                break;
            }
        }
        /* step3: change the auxiliary mux select control */
        val = (uint32_t)src << CLOCK_AUXSRC_POS;
        putreg32(val, addr);
        /* step4: switch the glitchless mux back to the aux mux */
        val |= 1;
        putreg32(val, addr);
        /* step5: if required, poll the SELECTED register until the switch is completed */
        while (1) {
            if (clock_ref_get_selected() & (1 << 1)) {
                break;
            }
        }
    }
}

/* div[9:8]: Integer component of the divisor, 0 is for 2^2 */
/* div[7:0]: reserved */
void clock_ref_set_div(uint32_t div)
{
    putreg32(div, CLOCKS_BASE + CLOCK_REF_DIV_OFFSET);
}

uint32_t clock_sys_get_selected(void)
{
    return getreg32(CLOCKS_BASE + CLOCK_SYS_SELECTED_OFFSET);
}

/* must: call clock_ref_set_src brfore call clock_sys_set_src */
void clock_sys_set_src(uint8_t src)
{
    uint32_t addr;
    uint32_t val;

    addr = CLOCKS_BASE + CLOCK_SYS_CTRL_OFFSET;
    if (src == CLOCK_SYS_SRC_REF_GLITCHLESS) {
        /* switch to the glitchless mux */
        /* step1: switch the glitchless mux to an alternate source */
        putreg32(0, addr);
        /* step2: poll the SELECTED register until the switch is completed */
        while (1) {
            if (clock_sys_get_selected() & (1 << 0)) {
                break;
            }
        }
    } else {
        /* switch to the auxiliary mux when the generator has a glitchless mux */
        /* step1: switch the glitchless mux to a source that isn’t the aux mux */
        putreg32(0, addr);
        /* step2: poll the SELECTED register until the switch is completed */
        while (1) {
            if (clock_sys_get_selected() & (1 << 0)) {
                break;
            }
        }
        /* step3: change the auxiliary mux select control */
        val = (uint32_t)src << CLOCK_AUXSRC_POS;
        putreg32(val, addr);
        /* step4: switch the glitchless mux back to the aux mux */
        val |= 1;
        putreg32(val, addr);
        /* step5: if required, poll the SELECTED register until the switch is completed */
        while (1) {
            if (clock_sys_get_selected() & (1 << 1)) {
                break;
            }
        }
    }
}

/* div[31:8]: Integer component of the divisor, 0 is for 2^24 */
/* div[ 7:0]: Fractional component of the divisor */
void clock_sys_set_div(uint32_t div)
{
    putreg32(div, CLOCKS_BASE + CLOCK_SYS_DIV_OFFSET);
}

void clock_peri_set(uint8_t enable, uint8_t src)
{
    uint32_t addr;
    uint32_t val;

    /* step1: disable clock */
    addr = CLOCKS_BASE + CLOCK_PERI_CTRL_OFFSET;
    putreg32(1 << CLOCK_ENABLE_POS, addr + REG_ALIAS_CLR_BITS);

    /* step2: config ctrl register */
    val = getreg32(addr);
    /* config clock source */
    val &= ~(CLOCK_AUXSRC_MASK << CLOCK_AUXSRC_POS);
    val |= ((src & CLOCK_AUXSRC_MASK) << CLOCK_AUXSRC_POS);
    /* disable clock */
    val &= ~(1 << CLOCK_ENABLE_POS);
    putreg32(val, addr);

    /* step3: config enable */
    if (enable) {
        putreg32(1 << CLOCK_ENABLE_POS, addr + REG_ALIAS_SET_BITS);
    }
}

/* div[9:8]: Integer component of the divisor, 0 is for 2^2 */
/* div[7:0]: reserved */
/* phase: 0 ~ 3 */
void clock_usb_set(uint8_t enable, uint8_t src, uint32_t div, uint8_t phase, uint8_t nudge)
{
    uint32_t addr;
    uint32_t val;

    /* step1: disable clock */
    addr = CLOCKS_BASE + CLOCK_USB_CTRL_OFFSET;
    putreg32(1 << CLOCK_ENABLE_POS, addr + REG_ALIAS_CLR_BITS);

    /* step2: config ctrl register */
    val = getreg32(addr);
    /* config clock source */
    val &= ~(CLOCK_AUXSRC_MASK << CLOCK_AUXSRC_POS);
    val |= ((src & CLOCK_AUXSRC_MASK) << CLOCK_AUXSRC_POS);
    /* config delay phase up to 3 cycles of the input clock */
    val &= ~(CLOCK_PHASE_MASK << CLOCK_PHASE_POS);
    val |= ((phase & CLOCK_PHASE_MASK) << CLOCK_PHASE_POS);
    /* config signal shifts the phase of the output by 1 cycle of the input clock */
    if (nudge) {
        val |= 1 << CLOCK_NUDGE_POS;
    } else {
        val &= ~(1 << CLOCK_NUDGE_POS);
    }
    /* disable clock */
    val &= ~(1 << CLOCK_ENABLE_POS);
    putreg32(val, addr);

    /* step3: config div */
    putreg32(div, CLOCKS_BASE + CLOCK_USB_DIV_OFFSET);

    /* step4: config enable */
    if (enable) {
        putreg32(1 << CLOCK_ENABLE_POS, addr + REG_ALIAS_SET_BITS);
    }
}

/* div[9:8]: Integer component of the divisor, 0 is for 2^2 */
/* div[7:0]: reserved */
/* phase: 0 ~ 3 */
void clock_adc_set(uint8_t enable, uint8_t src, uint32_t div, uint8_t phase, uint8_t nudge)
{
    uint32_t addr;
    uint32_t val;

    /* step1: disable clock */
    addr = CLOCKS_BASE + CLOCK_ADC_CTRL_OFFSET;
    putreg32(1 << CLOCK_ENABLE_POS, addr + REG_ALIAS_CLR_BITS);

    /* step2: config ctrl register */
    val = getreg32(addr);
    /* config clock source */
    val &= ~(CLOCK_AUXSRC_MASK << CLOCK_AUXSRC_POS);
    val |= ((src & CLOCK_AUXSRC_MASK) << CLOCK_AUXSRC_POS);
    /* config delay phase up to 3 cycles of the input clock */
    val &= ~(CLOCK_PHASE_MASK << CLOCK_PHASE_POS);
    val |= ((phase & CLOCK_PHASE_MASK) << CLOCK_PHASE_POS);
    /* config signal shifts the phase of the output by 1 cycle of the input clock */
    if (nudge) {
        val |= 1 << CLOCK_NUDGE_POS;
    } else {
        val &= ~(1 << CLOCK_NUDGE_POS);
    }
    /* disable clock */
    val &= ~(1 << CLOCK_ENABLE_POS);
    putreg32(val, addr);

    /* step3: config div */
    putreg32(div, CLOCKS_BASE + CLOCK_ADC_DIV_OFFSET);

    /* step4: config enable */
    if (enable) {
        putreg32(1 << CLOCK_ENABLE_POS, addr + REG_ALIAS_SET_BITS);
    }
}

/* div[31:8]: Integer component of the divisor, 0 is for 2^2 */
/* div[ 7:0]: Fractional component of the divisor */
/* phase: 0 ~ 3 */
void clock_rtc_set(uint8_t enable, uint8_t src, uint32_t div, uint8_t phase, uint8_t nudge)
{
    uint32_t addr;
    uint32_t val;

    /* step1: disable clock */
    addr = CLOCKS_BASE + CLOCK_RTC_CTRL_OFFSET;
    putreg32(1 << CLOCK_ENABLE_POS, addr + REG_ALIAS_CLR_BITS);

    /* step2: config ctrl register */
    val = getreg32(addr);
    /* config clock source */
    val &= ~(CLOCK_AUXSRC_MASK << CLOCK_AUXSRC_POS);
    val |= ((src & CLOCK_AUXSRC_MASK) << CLOCK_AUXSRC_POS);
    /* config delay phase up to 3 cycles of the input clock */
    val &= ~(CLOCK_PHASE_MASK << CLOCK_PHASE_POS);
    val |= ((phase & CLOCK_PHASE_MASK) << CLOCK_PHASE_POS);
    /* config signal shifts the phase of the output by 1 cycle of the input clock */
    if (nudge) {
        val |= 1 << CLOCK_NUDGE_POS;
    } else {
        val &= ~(1 << CLOCK_NUDGE_POS);
    }
    /* disable clock */
    val &= ~(1 << CLOCK_ENABLE_POS);
    putreg32(val, addr);

    /* step3: config div */
    putreg32(div, CLOCKS_BASE + CLOCK_RTC_DIV_OFFSET);

    /* step4: config enable */
    if (enable) {
        putreg32(1 << CLOCK_ENABLE_POS, addr + REG_ALIAS_SET_BITS);
    }
}

void clock_enable(uint8_t clock)
{
    putreg32(1 << CLOCK_ENABLE_POS, CLOCKS_BASE + CLOCK_CTRL_OFFSET + REG_ALIAS_SET_BITS + (uint32_t)clock * 0xC);
}

void clock_disable(uint8_t clock)
{
    putreg32(1 << CLOCK_ENABLE_POS, CLOCKS_BASE + CLOCK_CTRL_OFFSET + REG_ALIAS_CLR_BITS + (uint32_t)clock * 0xC);
}

void clock_kill(uint8_t clock)
{
    putreg32(1 << CLOCK_KILL_POS, CLOCKS_BASE + CLOCK_CTRL_OFFSET + REG_ALIAS_SET_BITS + (uint32_t)clock * 0xC);
    putreg32(1 << CLOCK_KILL_POS, CLOCKS_BASE + CLOCK_CTRL_OFFSET + REG_ALIAS_CLR_BITS + (uint32_t)clock * 0xC);
}
