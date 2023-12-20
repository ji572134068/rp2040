#ifndef __HARDWARE_SIO_REG_H__
#define __HARDWARE_SIO_REG_H__

#define SIO_CPUID_OFFSET            (0x000)
#define SIO_GPIO_IN_OFFSET          (0x004)
#define SIO_GPIO_HI_IN_OFFSET       (0x008)
#define SIO_GPIO_OUT_OFFSET         (0x010)
#define SIO_GPIO_OUT_SET_OFFSET     (0x014)
#define SIO_GPIO_OUT_CLR_OFFSET     (0x018)
#define SIO_GPIO_OUT_XOR_OFFSET     (0x01C)
#define SIO_GPIO_OE_OFFSET          (0x020)
#define SIO_GPIO_OE_SET_OFFSET      (0x024)
#define SIO_GPIO_OE_CLR_OFFSET      (0x028)
#define SIO_GPIO_OE_XOR_OFFSET      (0x02C)
#define SIO_GPIO_HI_OUT_OFFSET      (0x030)
#define SIO_GPIO_HI_OUT_SET_OFFSET  (0x034)
#define SIO_GPIO_HI_OUT_CLR_OFFSET  (0x038)
#define SIO_GPIO_HI_OUT_XOR_OFFSET  (0x03C)
#define SIO_GPIO_HI_OE_OFFSET       (0x040)
#define SIO_GPIO_HI_OE_SET_OFFSET   (0x044)
#define SIO_GPIO_HI_OE_CLR_OFFSET   (0x048)
#define SIO_GPIO_HI_OE_XOR_OFFSET   (0x04C)
#define SIO_FIFO_ST_OFFSET          (0x050)
#define SIO_FIFO_WR_OFFSET          (0x054)
#define SIO_FIFO_RD_OFFSET          (0x058)
#define SIO_SPINLOCK_ST_OFFSET      (0x05C)

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* __HARDWARE_SIO_REG_H__ */
