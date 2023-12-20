#include "reset.h"

void reset_enable(uint32_t reset)
{
    uint32_t reg_base;

    reg_base = RESETS_BASE + REG_ALIAS_SET_BITS;
    putreg32(reset, reg_base + RESET_RESET_OFFSET);
}

void reset_disable(uint32_t reset)
{
    uint32_t reg_base;

    reg_base = RESETS_BASE + REG_ALIAS_CLR_BITS;
    putreg32(reset, reg_base + RESET_RESET_OFFSET);
}

void reset(uint32_t reset)
{
    reset_enable(reset);
    reset_disable(reset);
}

uint32_t reset_get_state(uint32_t reset)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = RESETS_BASE;
    regval = getreg32(reg_base + RESET_RESET_DONE_OFFSET);
    regval = regval & reset;

    return regval;
}

void reset_wdg_bound(uint32_t reset)
{
    uint32_t reg_base;

    reg_base = RESETS_BASE + REG_ALIAS_SET_BITS;
    putreg32(reset, reg_base + RESET_WDSEL_OFFSET);
}

void reset_wdg_unbound(uint32_t reset)
{
    uint32_t reg_base;

    reg_base = RESETS_BASE + REG_ALIAS_CLR_BITS;
    putreg32(reset, reg_base + RESET_WDSEL_OFFSET);
}

uint32_t reset_get_wdg_bound_state(uint32_t reset)
{
    uint32_t reg_base;
    uint32_t regval;

    reg_base = RESETS_BASE;
    regval = getreg32(reg_base + RESET_WDSEL_OFFSET);
    regval = regval & reset;

    return regval;
}
