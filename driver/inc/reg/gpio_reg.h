#ifndef __HARDWARE_GPIO_REG_H__
#define __HARDWARE_GPIO_REG_H__

/* IO_BANK0_BASE @0x40014000 */
#define GPIO_STATUS_OFFSET            (0x000)
#define GPIO_CTRL_OFFSET              (0x004)
#define GPIO_INTR_OFFSET              (0x0F0) /* raw interrupts */
#define GPIO_INTE_PROC0_OFFSET        (0x100) /* interrupt enable for proc0 */
#define GPIO_INTF_PROC0_OFFSET        (0x110) /* interrupt force for proc0 */
#define GPIO_INTS_PROC0_OFFSET        (0x120) /* interrupt status after masking & forcing for proc0 */
#define GPIO_INTE_PROC1_OFFSET        (0x130) /* interrupt enable for proc1 */
#define GPIO_INTF_PROC1_OFFSET        (0x140) /* interrupt force for proc1 */
#define GPIO_INTS_PROC1_OFFSET        (0x150) /* interrupt status after masking & forcing for proc1 */
#define GPIO_INTE_DORMANT_WAKE_OFFSET (0x160) /* interrupt enable for dormant_wake */
#define GPIO_INTF_DORMANT_WAKE_OFFSET (0x170) /* interrupt force for dormant_wake */
#define GPIO_INTS_DORMANT_WAKE_OFFSET (0x180) /* interrupt status after masking & forcing for dormant_wake */

/* IO_QSPI_BASE @0x40018000 */
#define GPIO_QSPI_CLK_STATUS_OFFSET        (0x000) /* QSPI CLK GPIO status */
#define GPIO_QSPI_CLK_CTRL_OFFSET          (0x004) /* QSPI CLK GPIO control including function select and overrides */
#define GPIO_QSPI_CS_STATUS_OFFSET         (0x008) /* QSPI CS GPIO status */
#define GPIO_QSPI_CS_CTRL_OFFSET           (0x00C) /* QSPI CS GPIO control including function select and overrides */
#define GPIO_QSPI_IO0_STATUS_OFFSET        (0x010) /* QSPI IO0 GPIO status */
#define GPIO_QSPI_IO0_CTRL_OFFSET          (0x014) /* QSPI IO0 GPIO control including function select and overrides */
#define GPIO_QSPI_IO1_STATUS_OFFSET        (0x018) /* QSPI IO1 GPIO status */
#define GPIO_QSPI_IO1_CTRL_OFFSET          (0x01C) /* QSPI IO1 GPIO control including function select and overrides */
#define GPIO_QSPI_IO2_STATUS_OFFSET        (0x020) /* QSPI IO2 GPIO status */
#define GPIO_QSPI_IO2_CTRL_OFFSET          (0x024) /* QSPI IO2 GPIO control including function select and overrides */
#define GPIO_QSPI_IO3_STATUS_OFFSET        (0x028) /* QSPI IO3 GPIO status */
#define GPIO_QSPI_IO3_CTRL_OFFSET          (0x02C) /* QSPI IO3 GPIO control including function select and overrides */
#define GPIO_QSPI_INTR_OFFSET              (0x030) /* raw interrupts */
#define GPIO_QSPI_INTE_PROC0_OFFSET        (0x034) /* interrupt enable for proc0 */
#define GPIO_QSPI_INTF_PROC0_OFFSET        (0x038) /* interrupt force for proc0 */
#define GPIO_QSPI_INTS_PROC0_OFFSET        (0x03C) /* interrupt status after masking & forcing for proc0 */
#define GPIO_QSPI_INTE_PROC1_OFFSET        (0x040) /* interrupt enable for proc1 */
#define GPIO_QSPI_INTF_PROC1_OFFSET        (0x044) /* interrupt force for proc1 */
#define GPIO_QSPI_INTS_PROC1_OFFSET        (0x048) /* interrupt status after masking & forcing for proc1 */
#define GPIO_QSPI_INTE_DORMANT_WAKE_OFFSET (0x04C) /* interrupt enable for dormant_wake */
#define GPIO_QSPI_INTF_DORMANT_WAKE_OFFSET (0x050) /* interrupt force for dormant_wake */
#define GPIO_QSPI_INTS_DORMANT_WAKE_OFFSET (0x054) /* interrupt status after masking & forcing for dormant_wake */

/* PADS_BANK0_BASE @0x4001C000 */
#define GPIO_PADS_VOLTAGE_SELECT_OFFSET (0x000)
#define GPIO_PADS_CTRL_OFFSET           (0x004) /* pad control register */
#define GPIO_PADS_SWCLK_CTRL_OFFSET     (0x07C)
#define GPIO_PADS_SWDIO_CTRL_OFFSET     (0x080)

/* PADS_QSPI_BASE @0x40020000 */
#define GPIO_PADS_QSPI_VOLTAGE_SELECT_OFFSET (0x000)
#define GPIO_PADS_QSPI_CLK_CTRL_OFFSET       (0x004)
#define GPIO_PADS_QSPI_IO0_CTRL_OFFSET       (0x008)
#define GPIO_PADS_QSPI_IO1_CTRL_OFFSET       (0x00C)
#define GPIO_PADS_QSPI_IO2_CTRL_OFFSET       (0x010)
#define GPIO_PADS_QSPI_IO3_CTRL_OFFSET       (0x014)
#define GPIO_PADS_QSPI_CS_CTRL_OFFSET        (0x018)

/* GPIO_STATUS_OFFSET */
#define GPIO_STATUS_OE_FROM_PERI (1 << 12)
#define GPIO_STATUS_OE_TO_PAD    (1 << 13)
#define GPIO_STATUS_IN_FROM_PAD  (1 << 17)
#define GPIO_STATUS_IN_TO_PERI   (1 << 19)
#define GPIO_STATUS_IRQ_FROM_PAD (1 << 24)
#define GPIO_STATUS_IRQ_TO_PROC  (1 << 26)
#define GPIO_STATUS_ALL          (GPIO_STATUS_OE_FROM_PERI | \
                                  GPIO_STATUS_OE_TO_PAD    | \
                                  GPIO_STATUS_IN_FROM_PAD  | \
                                  GPIO_STATUS_IN_TO_PERI   | \
                                  GPIO_STATUS_IRQ_FROM_PAD | \
                                  GPIO_STATUS_IRQ_TO_PROC)

/* GPIO_CTRL_OFFSET */
#define GPIO_FUNC_POS      (0)
#define GPIO_FUNC_MASK     (0x1F)
#define GPIO_OVER_OUT_POS  (8)
#define GPIO_OVER_OUT_MASK (3)
#define GPIO_OVER_OE_POS   (12)
#define GPIO_OVER_OE_MASK  (3)
#define GPIO_OVER_IN_POS   (16)
#define GPIO_OVER_IN_MASK  (3)
#define GPIO_OVER_IRQ_POS  (28)
#define GPIO_OVER_IRQ_MASK (3)

/* GPIO_PADS_CTRL_OFFSET */
#define GPIO_PADS_SLEW_RATE_POS  (0)
#define GPIO_PADS_SCHMITT_POS    (1)
#define GPIO_PADS_PULL_DOWN_POS  (2)
#define GPIO_PADS_PULL_UP_POS    (3)
#define GPIO_PADS_DRIVE_POS      (4)
#define GPIO_PADS_DRIVE_MASK     (3)
#define GPIO_PADS_IE_POS         (6)
#define GPIO_PADS_OD_POS         (7)

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* __HARDWARE_GPIO_REG_H__ */
