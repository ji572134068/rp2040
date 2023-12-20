#ifndef __HARDWARE_SYSTEM_REG_H__
#define __HARDWARE_SYSTEM_REG_H__

/* VREG_AND_CHIP_RESET_BASE @0x40064000 */
#define SYSTEM_VREG_OFFSET       (0x000)
#define SYSTEM_BOD_OFFSET        (0x004)
#define SYSTEM_CHIP_RESET_OFFSET (0x008)

/* PSM_BASE @0x40010000 */
#define SYSTEM_PSM_FRCE_ON_OFFSET  (0x000)
#define SYSTEM_PSM_FRCE_OFF_OFFSET (0x004)
#define SYSTEM_PSM_WDSEL_OFFSET    (0x008)
#define SYSTEM_PSM_DONE_OFFSET     (0x00C)

/* SYSTEM_VREG_OFFSET */
#define SYSTEM_VREG_EN_POS    (0)
#define SYSTEM_VREG_HIZ_POS   (1)
#define SYSTEM_VREG_VSEL_POS  (4)
#define SYSTEM_VREG_VSEL_MASK (0xF)
#define SYSTEM_VREG_ROK_POS   (12)

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* __HARDWARE_SYSTEM_REG_H__ */
