#include "gpio.h"

uint8_t gpio_read(uint8_t pin)
{
    uint32_t val;

    val = getreg32(SIO_BASE + SIO_GPIO_IN_OFFSET);
    val = val & (1 << pin);
    if (val) {
        return 1;
    } else {
        return 0;
    }
}

void gpio_write(uint8_t pin, uint8_t value)
{
    if (value) {
        putreg32(1 << pin, SIO_BASE + SIO_GPIO_OUT_SET_OFFSET);
    } else {
        putreg32(1 << pin, SIO_BASE + SIO_GPIO_OUT_CLR_OFFSET);
    }
}

void gpio_set(uint8_t pin)
{
    putreg32(1 << pin, SIO_BASE + SIO_GPIO_OUT_SET_OFFSET);
}

void gpio_clear(uint8_t pin)
{
    putreg32(1 << pin, SIO_BASE + SIO_GPIO_OUT_CLR_OFFSET);
}

void gpio_toggle(uint8_t pin)
{
    putreg32(1 << pin, SIO_BASE + SIO_GPIO_OUT_XOR_OFFSET);
}

void gpio_oe_write(uint8_t pin, uint8_t value)
{
    if (value) {
        putreg32(1 << pin, SIO_BASE + SIO_GPIO_OE_SET_OFFSET);
    } else {   
        putreg32(1 << pin, SIO_BASE + SIO_GPIO_OE_CLR_OFFSET);
    }
}

void gpio_oe_set(uint8_t pin)
{
    putreg32(1 << pin, SIO_BASE + SIO_GPIO_OE_SET_OFFSET);
}

void gpio_oe_clear(uint8_t pin)
{
    putreg32(1 << pin, SIO_BASE + SIO_GPIO_OE_CLR_OFFSET);
}

void gpio_oe_toggle(uint8_t pin)
{
    putreg32(1 << pin, SIO_BASE + SIO_GPIO_OE_XOR_OFFSET);
}

uint32_t gpio_read_multi(void)
{
    return getreg32(SIO_BASE + SIO_GPIO_IN_OFFSET);
}

void gpio_write_multi(uint32_t value)
{
    putreg32(value, SIO_BASE + SIO_GPIO_OUT_OFFSET);
}

void gpio_set_multi(uint32_t pins)
{
    putreg32(pins, SIO_BASE + SIO_GPIO_OUT_SET_OFFSET);
}

void gpio_clear_multi(uint32_t pins)
{
    putreg32(pins, SIO_BASE + SIO_GPIO_OUT_CLR_OFFSET);
}

void gpio_toggle_multi(uint32_t pins)
{
    putreg32(pins, SIO_BASE + SIO_GPIO_OUT_XOR_OFFSET);
}

void gpio_oe_write_multi(uint32_t value)
{
    putreg32(value, SIO_BASE + SIO_GPIO_OE_OFFSET);
}

void gpio_oe_set_multi(uint32_t pins)
{
    putreg32(pins, SIO_BASE + SIO_GPIO_OE_SET_OFFSET);
}

void gpio_oe_clear_multi(uint32_t pins)
{
    putreg32(pins, SIO_BASE + SIO_GPIO_OE_CLR_OFFSET);
}

void gpio_oe_toggle_multi(uint32_t pins)
{
    putreg32(pins, SIO_BASE + SIO_GPIO_OE_XOR_OFFSET);
}

uint32_t gpio_get_status(uint8_t pin, uint32_t status)
{
    uint32_t val;

    val = getreg32(IO_BANK0_BASE + GPIO_STATUS_OFFSET + pin * 8);
    return (val & status);
}

void gpio_func_sel(uint8_t pin, uint8_t func)
{
    uint32_t addr;
    uint32_t val;

    addr = IO_BANK0_BASE + GPIO_CTRL_OFFSET + pin * 8;
    val = getreg32(addr);
    val &= ~(GPIO_FUNC_MASK << GPIO_FUNC_POS);
    val |= (uint32_t)func << GPIO_FUNC_POS;
    putreg32(val, addr);
}

void gpio_over_out_set(uint8_t pin, uint8_t over)
{
    uint32_t addr;
    uint32_t val;

    addr = IO_BANK0_BASE + GPIO_CTRL_OFFSET + pin * 8;
    val = getreg32(addr);
    val &= ~(GPIO_OVER_OUT_MASK << GPIO_OVER_OUT_POS);
    val |= (uint32_t)over << GPIO_OVER_OUT_POS;
    putreg32(val, addr);
}

void gpio_over_oe_set(uint8_t pin, uint8_t over)
{
    uint32_t addr;
    uint32_t val;

    addr = IO_BANK0_BASE + GPIO_CTRL_OFFSET + pin * 8;
    val = getreg32(addr);
    val &= ~(GPIO_OVER_OE_MASK << GPIO_OVER_OE_POS);
    val |= (uint32_t)over << GPIO_OVER_OE_POS;
    putreg32(val, addr);
}

void gpio_over_in_set(uint8_t pin, uint8_t over)
{
    uint32_t addr;
    uint32_t val;

    addr = IO_BANK0_BASE + GPIO_CTRL_OFFSET + pin * 8;
    val = getreg32(addr);
    val &= ~(GPIO_OVER_IN_MASK << GPIO_OVER_IN_POS);
    val |= (uint32_t)over << GPIO_OVER_IN_POS;
    putreg32(val, addr);
}

void gpio_over_irq_set(uint8_t pin, uint8_t over)
{
    uint32_t addr;
    uint32_t val;

    addr = IO_BANK0_BASE + GPIO_CTRL_OFFSET + pin * 8;
    val = getreg32(addr);
    val &= ~(GPIO_OVER_IRQ_MASK << GPIO_OVER_IRQ_POS);
    val |= (uint32_t)over << GPIO_OVER_IRQ_POS;
    putreg32(val, addr);
}

void gpio_init(struct gpio_cfg_s *cfg)
{
    uint32_t addr;
    uint32_t val;
    uint32_t offset;

    if (cfg->sio_dir == GPIO_SIO_DIR_OUT) {
        gpio_oe_set(cfg->pin);
    } else {
        gpio_oe_clear(cfg->pin);
    }

    offset = cfg->pin << 3; /* cfg->pin * 8 */
    addr = IO_BANK0_BASE + GPIO_CTRL_OFFSET;
    val = cfg->funcsel << GPIO_FUNC_POS;
    val |= cfg->over_out << GPIO_OVER_OUT_POS;
    val |= cfg->over_oe << GPIO_OVER_OE_POS;
    val |= cfg->over_in << GPIO_OVER_IN_POS;
    val |= cfg->over_irq << GPIO_OVER_IRQ_POS;
    putreg32(val, addr + offset);

    offset = cfg->pin << 2; /* cfg->pin * 4 */
    addr = PADS_BANK0_BASE + GPIO_PADS_CTRL_OFFSET;
    val = cfg->slew_rate << GPIO_PADS_SLEW_RATE_POS;
    val |= cfg->schmitt << GPIO_PADS_SCHMITT_POS;
    val |= cfg->pull_down << GPIO_PADS_PULL_DOWN_POS;
    val |= cfg->pull_up << GPIO_PADS_PULL_UP_POS;
    val |= cfg->drive << GPIO_PADS_DRIVE_POS;
    val |= cfg->ie << GPIO_PADS_IE_POS;
    val |= cfg->od << GPIO_PADS_OD_POS;
    putreg32(val, addr + offset);
}

uint8_t gpio_irq_get_raw_status(uint8_t pin, uint8_t irq)
{
    uint32_t addr;
    uint32_t val;
    uint32_t offset;
    uint32_t pos;

    offset = (pin >> 3) << 2; /* offset = pin / 8 * 4 */
    pos = (pin & 7) << 2; /* pos = (pin % 8) * 4 */
    addr = IO_BANK0_BASE + GPIO_INTR_OFFSET;
    val = getreg32(addr + offset);
    return (uint8_t)((val >> pos) & irq);
}

void gpio_irq_raw_status_clear(uint8_t pin, uint8_t irq)
{
    uint32_t addr;
    uint32_t val;
    uint32_t offset;
    uint32_t pos;

    offset = (pin >> 3) << 2; /* offset = pin / 8 * 4 */
    pos = (pin & 7) << 2; /* pos = (pin % 8) * 4 */
    addr = IO_BANK0_BASE + GPIO_INTR_OFFSET;
    val = (uint32_t)irq << pos;
    putreg32(val, addr + offset);
}

void gpio_irq_enable_proc0(uint8_t pin, uint8_t irq)
{
    uint32_t addr;
    uint32_t val;
    uint32_t offset;
    uint32_t pos;

    offset = (pin >> 3) << 2; /* offset = pin / 8 * 4 */
    pos = (pin & 7) << 2; /* pos = (pin % 8) * 4 */
    addr = IO_BANK0_BASE + GPIO_INTE_PROC0_OFFSET + REG_ALIAS_SET_BITS;
    val = (uint32_t)irq << pos;
    putreg32(val, addr + offset);
}

void gpio_irq_disable_proc0(uint8_t pin, uint8_t irq)
{
    uint32_t addr;
    uint32_t val;
    uint32_t offset;
    uint32_t pos;

    offset = (pin >> 3) << 2; /* offset = pin / 8 * 4 */
    pos = (pin & 7) << 2; /* pos = (pin % 8) * 4 */
    addr = IO_BANK0_BASE + GPIO_INTE_PROC0_OFFSET + REG_ALIAS_CLR_BITS;
    val = (uint32_t)irq << pos;
    putreg32(val, addr + offset);
}

void gpio_irq_force_proc0(uint8_t pin, uint8_t irq)
{
    uint32_t addr;
    uint32_t val;
    uint32_t offset;
    uint32_t pos;

    offset = (pin >> 3) << 2; /* offset = pin / 8 * 4 */
    pos = (pin & 7) << 2; /* pos = (pin % 8) * 4 */
    addr = IO_BANK0_BASE + GPIO_INTF_PROC0_OFFSET + REG_ALIAS_SET_BITS;
    val = (uint32_t)irq << pos;
    putreg32(val, addr + offset);
}

void gpio_irq_deforce_proc0(uint8_t pin, uint8_t irq)
{
    uint32_t addr;
    uint32_t val;
    uint32_t offset;
    uint32_t pos;

    offset = (pin >> 3) << 2; /* offset = pin / 8 * 4 */
    pos = (pin & 7) << 2; /* pos = (pin % 8) * 4 */
    addr = IO_BANK0_BASE + GPIO_INTF_PROC0_OFFSET + REG_ALIAS_CLR_BITS;
    val = (uint32_t)irq << pos;
    putreg32(val, addr + offset);
}

uint8_t gpio_irq_get_status_proc0(uint8_t pin, uint8_t irq)
{
    uint32_t addr;
    uint32_t val;
    uint32_t offset;
    uint32_t pos;

    offset = (pin >> 3) << 2; /* offset = pin / 8 * 4 */
    pos = (pin & 7) << 2; /* pos = (pin % 8) * 4 */
    addr = IO_BANK0_BASE + GPIO_INTS_PROC0_OFFSET;
    val = getreg32(addr + offset);
    return (uint8_t)((val >> pos) & irq);
}

void gpio_irq_enable_proc1(uint8_t pin, uint8_t irq)
{
    uint32_t addr;
    uint32_t val;
    uint32_t offset;
    uint32_t pos;

    offset = (pin >> 3) << 2; /* offset = pin / 8 * 4 */
    pos = (pin & 7) << 2; /* pos = (pin % 8) * 4 */
    addr = IO_BANK0_BASE + GPIO_INTE_PROC1_OFFSET + REG_ALIAS_SET_BITS;
    val = (uint32_t)irq << pos;
    putreg32(val, addr + offset);
}

void gpio_irq_disable_proc1(uint8_t pin, uint8_t irq)
{
    uint32_t addr;
    uint32_t val;
    uint32_t offset;
    uint32_t pos;

    offset = (pin >> 3) << 2; /* offset = pin / 8 * 4 */
    pos = (pin & 7) << 2; /* pos = (pin % 8) * 4 */
    addr = IO_BANK0_BASE + GPIO_INTE_PROC1_OFFSET + REG_ALIAS_CLR_BITS;
    val = (uint32_t)irq << pos;
    putreg32(val, addr + offset);
}

void gpio_irq_force_proc1(uint8_t pin, uint8_t irq)
{
    uint32_t addr;
    uint32_t val;
    uint32_t offset;
    uint32_t pos;

    offset = (pin >> 3) << 2; /* offset = pin / 8 * 4 */
    pos = (pin & 7) << 2; /* pos = (pin % 8) * 4 */
    addr = IO_BANK0_BASE + GPIO_INTF_PROC1_OFFSET + REG_ALIAS_SET_BITS;
    val = (uint32_t)irq << pos;
    putreg32(val, addr + offset);
}

void gpio_irq_deforce_proc1(uint8_t pin, uint8_t irq)
{
    uint32_t addr;
    uint32_t val;
    uint32_t offset;
    uint32_t pos;

    offset = (pin >> 3) << 2; /* offset = pin / 8 * 4 */
    pos = (pin & 7) << 2; /* pos = (pin % 8) * 4 */
    addr = IO_BANK0_BASE + GPIO_INTF_PROC1_OFFSET + REG_ALIAS_CLR_BITS;
    val = (uint32_t)irq << pos;
    putreg32(val, addr + offset);
}

uint8_t gpio_irq_get_status_proc1(uint8_t pin, uint8_t irq)
{
    uint32_t addr;
    uint32_t val;
    uint32_t offset;
    uint32_t pos;

    offset = (pin >> 3) << 2; /* offset = pin / 8 * 4 */
    pos = (pin & 7) << 2; /* pos = (pin % 8) * 4 */
    addr = IO_BANK0_BASE + GPIO_INTS_PROC1_OFFSET;
    val = getreg32(addr + offset);
    return (uint8_t)((val >> pos) & irq);
}

void gpio_irq_enable_dormant(uint8_t pin, uint8_t irq)
{
    uint32_t addr;
    uint32_t val;
    uint32_t offset;
    uint32_t pos;

    offset = (pin >> 3) << 2; /* offset = pin / 8 * 4 */
    pos = (pin & 7) << 2; /* pos = (pin % 8) * 4 */
    addr = IO_BANK0_BASE + GPIO_INTE_DORMANT_WAKE_OFFSET + REG_ALIAS_SET_BITS;
    val = (uint32_t)irq << pos;
    putreg32(val, addr + offset);
}

void gpio_irq_disable_dormant(uint8_t pin, uint8_t irq)
{
    uint32_t addr;
    uint32_t val;
    uint32_t offset;
    uint32_t pos;

    offset = (pin >> 3) << 2; /* offset = pin / 8 * 4 */
    pos = (pin & 7) << 2; /* pos = (pin % 8) * 4 */
    addr = IO_BANK0_BASE + GPIO_INTE_DORMANT_WAKE_OFFSET + REG_ALIAS_CLR_BITS;
    val = (uint32_t)irq << pos;
    putreg32(val, addr + offset);
}

void gpio_irq_force_dormant(uint8_t pin, uint8_t irq)
{
    uint32_t addr;
    uint32_t val;
    uint32_t offset;
    uint32_t pos;

    offset = (pin >> 3) << 2; /* offset = pin / 8 * 4 */
    pos = (pin & 7) << 2; /* pos = (pin % 8) * 4 */
    addr = IO_BANK0_BASE + GPIO_INTF_DORMANT_WAKE_OFFSET + REG_ALIAS_SET_BITS;
    val = (uint32_t)irq << pos;
    putreg32(val, addr + offset);
}

void gpio_irq_deforce_dormant(uint8_t pin, uint8_t irq)
{
    uint32_t addr;
    uint32_t val;
    uint32_t offset;
    uint32_t pos;

    offset = (pin >> 3) << 2; /* offset = pin / 8 * 4 */
    pos = (pin & 7) << 2; /* pos = (pin % 8) * 4 */
    addr = IO_BANK0_BASE + GPIO_INTF_DORMANT_WAKE_OFFSET + REG_ALIAS_CLR_BITS;
    val = (uint32_t)irq << pos;
    putreg32(val, addr + offset);
}
uint8_t gpio_irq_get_status_dormant(uint8_t pin, uint8_t irq)
{
    uint32_t addr;
    uint32_t val;
    uint32_t offset;
    uint32_t pos;

    offset = (pin >> 3) << 2; /* offset = pin / 8 * 4 */
    pos = (pin & 7) << 2; /* pos = (pin % 8) * 4 */
    addr = IO_BANK0_BASE + GPIO_INTS_DORMANT_WAKE_OFFSET;
    val = getreg32(addr + offset);
    return (uint8_t)((val >> pos) & irq);
}
