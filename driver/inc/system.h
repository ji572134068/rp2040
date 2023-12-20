#ifndef __HARDWARE_SYSTEM_H__
#define __HARDWARE_SYSTEM_H__

#include "reg.h"
#include "system_reg.h"

#define SYSTEM_REGULATOR_VOLTAGE_DISABLE (0)
#define SYSTEM_REGULATOR_VOLTAGE_0P80V   (5)
#define SYSTEM_REGULATOR_VOLTAGE_0P85V   (6)
#define SYSTEM_REGULATOR_VOLTAGE_0P90V   (7)
#define SYSTEM_REGULATOR_VOLTAGE_0P95V   (8)
#define SYSTEM_REGULATOR_VOLTAGE_1P00V   (9)
#define SYSTEM_REGULATOR_VOLTAGE_1P05V   (10)
#define SYSTEM_REGULATOR_VOLTAGE_1P10V   (11)
#define SYSTEM_REGULATOR_VOLTAGE_1P15V   (12)
#define SYSTEM_REGULATOR_VOLTAGE_1P20V   (13)
#define SYSTEM_REGULATOR_VOLTAGE_1P25V   (14)
#define SYSTEM_REGULATOR_VOLTAGE_1P30V   (15)
#define SYSTEM_REGULATOR_VOLTAGE_DEFAULT (11)

#define SYSTEM_BLOCK_ROSC                (1 << 0)
#define SYSTEM_BLOCK_XOSC                (1 << 1)
#define SYSTEM_BLOCK_CLOCKS              (1 << 2)
#define SYSTEM_BLOCK_RESETS              (1 << 3)
#define SYSTEM_BLOCK_BUSFABRIC           (1 << 4)
#define SYSTEM_BLOCK_ROM                 (1 << 5)
#define SYSTEM_BLOCK_SRAM0               (1 << 6)
#define SYSTEM_BLOCK_SRAM1               (1 << 7)
#define SYSTEM_BLOCK_SRAM2               (1 << 8)
#define SYSTEM_BLOCK_SRAM3               (1 << 9)
#define SYSTEM_BLOCK_SRAM4               (1 << 10)
#define SYSTEM_BLOCK_SRAM5               (1 << 11)
#define SYSTEM_BLOCK_XIP                 (1 << 12)
#define SYSTEM_BLOCK_VREG_AND_CHIP_RESET (1 << 13)
#define SYSTEM_BLOCK_SIO                 (1 << 14)
#define SYSTEM_BLOCK_PROC0               (1 << 15)
#define SYSTEM_BLOCK_PROC1               (1 << 16)

#ifdef __cplusplus
extern "C" {
#endif

void system_regulator_set(uint8_t voltage);

void system_power_off(uint32_t block);
void system_power_on(uint32_t block);
void system_reset(uint32_t block);
void system_wdg_bound(uint32_t block);
void system_wdg_unbound(uint32_t block);
uint8_t system_block_is_available(uint32_t block);

#ifdef __cplusplus
}
#endif

#endif /* __HARDWARE_SYSTEM_H__ */
