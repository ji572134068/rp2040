/*************************************************************************//**
 * @file     system_RP2040.c
 * @brief    CMSIS-Core(M) Device Peripheral Access Layer Header File for
 *           Device RP2040
 * @version  V1.0.0
 * @date     5. May 2021
 *****************************************************************************/
/*
 * Copyright (c) 2009-2021 Arm Limited. All rights reserved.
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include "RP2040.h"
#include "system.h"
#include "clock.h"

/*---------------------------------------------------------------------------
  System Core Clock Variable
 *---------------------------------------------------------------------------*/
#define MacroSystemCoreClock (400 * 1000 * 1000)
uint32_t SystemCoreClock; /* System Clock Frequency (Core Clock)*/
volatile uint32_t tick_1ms;

/*---------------------------------------------------------------------------
  System Core Clock function
 *---------------------------------------------------------------------------*/
void SystemCoreClockUpdate (void)
{
    SystemCoreClock = MacroSystemCoreClock;
}

/*---------------------------------------------------------------------------
  System initialization function
 *---------------------------------------------------------------------------*/
void __attribute__((constructor)) SystemInit (void)
{
    system_regulator_set(SYSTEM_REGULATOR_VOLTAGE_1P30V);
    clock_ref_set_src(CLOCK_REF_SRC_XOSC_GLITCHLESS);
    clock_sys_set_src(CLOCK_SYS_SRC_REF_GLITCHLESS);
    clock_pll_init(CLOCK_PLL_SYSPLL, 1, 100, 3, 1); /* 12MHz * 100 / 3 / 1 = 400MHz */
    clock_sys_set_div(1 << 8);                      /* 400MHz / 1 = 400MHz */
    clock_sys_set_src(CLOCK_SYS_SRC_SYSPLL);

    SystemCoreClockUpdate();

    /* 1ms */
    SysTick_Config(MacroSystemCoreClock / 1000);
}

void isr_systick(void)
{
    tick_1ms++;
}