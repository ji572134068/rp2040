#include "RP2040.h"
#include "sio.h"
#include "common.h"

uint8_t get_core(void)
{
    return getreg8(SIO_BASE + SIO_CPUID_OFFSET);
}

/* return 0: success.  return 1: fifo full, failed */
uint8_t sio_fifo_write(uint32_t data)
{
    if (sio_fifo_get_status(SIO_FIFO_STATUS_TX_RDY)) {
        putreg32(data, SIO_BASE + SIO_FIFO_WR_OFFSET);
        return 0;
    } else {
        return 1;
    }
}

/* return 0: success.  return 1: fifo empty, failed */
uint8_t sio_fifo_read(uint32_t *data)
{
    if (sio_fifo_get_status(SIO_FIFO_STATUS_RX_VLD)) {
        *data = getreg32(SIO_BASE + SIO_FIFO_RD_OFFSET);
        return 0;
    } else {
        return 1;
    }
}

void sio_fifo_write_blocking(uint32_t data)
{
    while (1) {
        if (sio_fifo_get_status(SIO_FIFO_STATUS_TX_RDY)) {
            putreg32(data, SIO_BASE + SIO_FIFO_WR_OFFSET);
            break;
        }
    }
}

uint32_t sio_fifo_read_blocking(void)
{
    while (1) {
        if (sio_fifo_get_status(SIO_FIFO_STATUS_RX_VLD)) {
            return getreg32(SIO_BASE + SIO_FIFO_RD_OFFSET);
        }
    }
}

uint8_t sio_fifo_get_status(uint8_t status)
{
    uint8_t val;

    val = getreg8(SIO_BASE + SIO_FIFO_ST_OFFSET);
    val &= status;
    return val;
}

void sio_fifo_rx_drain(void)
{
    uint8_t status;

    while (1) {
        status = sio_fifo_get_status(SIO_FIFO_STATUS_RX_VLD);
        if (status) {
            getreg32(SIO_BASE + SIO_FIFO_RD_OFFSET);
        } else {
            break;
        }
    }
}

void sio_launch_core1(void (*entry)(void), uint32_t *sp, uint32_t vector_table)
{
    uint32_t irq_enabled;
    uint32_t seq;
    uint32_t cmd;
    uint32_t response;

    irq_enabled = __NVIC_GetEnableIRQ(SIO_IRQ_PROC0_IRQn);
    __NVIC_DisableIRQ(SIO_IRQ_PROC0_IRQn);

    const uint32_t cmd_sequence[] = {0, 0, 1, vector_table, (uint32_t)sp, (uint32_t)entry};
    seq = 0;
    do {
        cmd = cmd_sequence[seq] ;
        if (cmd == 0) {
            sio_fifo_rx_drain();
            __sev(); /* Execute a SEV as core 1 may be waiting for FIFO space via WFE */
        }
        sio_fifo_write_blocking(cmd);
        __sev();
        response = sio_fifo_read_blocking();
        if (cmd == response) {
            seq++;
        } else {
            seq = 0;
        }
    } while (seq < sizeof(cmd_sequence) / sizeof(cmd_sequence[0]));
    if (irq_enabled) {
        __NVIC_EnableIRQ(SIO_IRQ_PROC0_IRQn);
    }
}
