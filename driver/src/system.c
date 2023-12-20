#include "system.h"

/* voltage: SYSTEM_REGULATOR_VOLTAGE_XXX */
void system_regulator_set(uint8_t voltage)
{
    uint32_t addr;
    uint32_t val;

    addr = VREG_AND_CHIP_RESET_BASE + SYSTEM_VREG_OFFSET;
    if (voltage == SYSTEM_REGULATOR_VOLTAGE_DISABLE) {
        /* disable voltage regulator */
        putreg32(1 << SYSTEM_VREG_EN_POS, addr + REG_ALIAS_CLR_BITS);
    } else {
        /* config output voltage of regulator */
        val = getreg32(addr);
        val &= ~(SYSTEM_VREG_VSEL_MASK << SYSTEM_VREG_VSEL_POS);
        val |= (voltage << SYSTEM_VREG_VSEL_POS);
        putreg32(val, addr);
        /* check if ENABLE or DISABLE */
        val &= (1 << SYSTEM_VREG_EN_POS);
        if (val == 0) {
            /* enable voltage regulator */
            putreg32(1 << SYSTEM_VREG_EN_POS, addr + REG_ALIAS_SET_BITS);
        }
        /* wait for regulation status OK */
        while (1) {
            val = getreg32(addr);
            val &= (1 << SYSTEM_VREG_ROK_POS);
            if (val) {
                break;
            }
        }
    }
}

/* block: SYSTEM_BLOCK_XXX */
void system_power_off(uint32_t block)
{
    putreg32(block, PSM_BASE + SYSTEM_PSM_FRCE_ON_OFFSET + REG_ALIAS_CLR_BITS);
    putreg32(block, PSM_BASE + SYSTEM_PSM_FRCE_OFF_OFFSET + REG_ALIAS_SET_BITS);
}

/* block: SYSTEM_BLOCK_XXX */
void system_power_on(uint32_t block)
{
    putreg32(block, PSM_BASE + SYSTEM_PSM_FRCE_OFF_OFFSET + REG_ALIAS_CLR_BITS);
    putreg32(block, PSM_BASE + SYSTEM_PSM_FRCE_ON_OFFSET + REG_ALIAS_SET_BITS);
    while (1) {
        if (system_block_is_available(block)) {
            return;
        }
    }
}

/* block: SYSTEM_BLOCK_XXX */
void system_reset(uint32_t block)
{
    system_power_off(block);
    system_power_on(block);
}

/* block: SYSTEM_BLOCK_XXX */
void system_wdg_bound(uint32_t block)
{
    putreg32(block, PSM_BASE + SYSTEM_PSM_WDSEL_OFFSET + REG_ALIAS_SET_BITS);
}

/* block: SYSTEM_BLOCK_XXX */
void system_wdg_unbound(uint32_t block)
{
    putreg32(block, PSM_BASE + SYSTEM_PSM_WDSEL_OFFSET + REG_ALIAS_CLR_BITS);
}

/* block: SYSTEM_BLOCK_XXX */
uint8_t system_block_is_available(uint32_t block)
{
    uint32_t val;

    val = getreg32(PSM_BASE + SYSTEM_PSM_DONE_OFFSET);
    val = val & block;
    if (val == block) {
        return 1;
    } else {
        return 0;
    }
}
