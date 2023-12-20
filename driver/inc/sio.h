#ifndef __HARDWARE_SIO_H__
#define __HARDWARE_SIO_H__

#include "reg.h"
#include "sio_reg.h"

#define CORE_0 (0)
#define CORE_1 (1)

#define SIO_FIFO_STATUS_RX_VLD    (1 << 0) /* rx fifo is not empty */
#define SIO_FIFO_STATUS_TX_RDY    (1 << 1) /* tx fifo is not full */
#define SIO_FIFO_STATUS_WRITE_BAD (1 << 2) /* tx fifo was written when full, this write was ignored */
#define SIO_FIFO_STATUS_READ_BAD  (1 << 3) /* rx fifo was read when empty, this read was ignored */

#ifdef __cplusplus
extern "C" {
#endif

uint8_t get_core(void);

uint8_t sio_fifo_write(uint32_t data);
uint8_t sio_fifo_read(uint32_t *data);
void sio_fifo_write_blocking(uint32_t data);
uint32_t sio_fifo_read_blocking(void);
uint8_t sio_fifo_get_status(uint8_t status);
void sio_fifo_rx_drain(void);
void sio_launch_core1(void (*entry)(void), uint32_t *sp, uint32_t vector_table);

#ifdef __cplusplus
}
#endif

#endif /* __HARDWARE_SIO_H__ */
