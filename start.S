.syntax unified
.cpu cortex-m0plus
.thumb

.global  _vector
.global  isr_default
.global  isr_valid
.global  isr_reset

.section  .text.isr_reset
.weak  isr_reset
.type  isr_reset, %function
isr_reset:
    /* disable irq */
    cpsid i
    ldr r0, =0xE000E180
    ldr r1, =0xFFFFFFFF
    str r1, [r0]
    ldr r0, =0xE000E280
    ldr r1, =0xFFFFFFFF
    str r1, [r0]
    /* relocate VTOR, vector table offset register */
    ldr r0, =0xE000ED08
    ldr r1, =_vector_load
    str r1, [r0]
    /* set MSP, main stack point */
    ldr r0, =_stack_top
    msr msp, r0
    /* load data section */
    ldr r0, =_data_load
    ldr r1, =_data_run
    ldr r2, =_data_run_end
    cmp r1, r2
    bhs 2f
1:
    ldr r3, [r0]
    str r3, [r1]
    adds r0, r0, #4
    adds r1, r1, #4
    cmp r1, r2
    blo 1b
2:
    /* clear bss section */
    ldr r0, =0
    ldr r1, =_bss_run
    ldr r2, =_bss_run_end
    cmp r1, r2
    bhs 2f
1:
    str r0, [r1]
    adds r1, r1, #4
    cmp r1, r2
    blo 1b
2:
    bl  SystemInit
    bl  main
    b  .
.size  isr_reset, .-isr_reset

.section  .text.isr_default,"ax",%progbits
isr_default:
    b  isr_default
.size  isr_default, .-isr_default

.section  .text.isr_invalid,"ax",%progbits
isr_invalid:
    b  isr_invalid
.size  isr_invalid, .-isr_invalid

.section  .isr_vector,"a",%progbits
.type  _vector, %object
_vector:
    .word  _stack_top
    .word  isr_reset
    .word  isr_nmi
    .word  isr_hardfault
    .word  isr_invalid /* reserved, should never fire */
    .word  isr_invalid /* reserved, should never fire */
    .word  isr_invalid /* reserved, should never fire */
    .word  isr_invalid /* reserved, should never fire */
    .word  isr_invalid /* reserved, should never fire */
    .word  isr_invalid /* reserved, should never fire */
    .word  isr_invalid /* reserved, should never fire */
    .word  isr_svcall
    .word  isr_invalid /* reserved, should never fire */
    .word  isr_invalid /* reserved, should never fire */
    .word  isr_pendsv
    .word  isr_systick
    /* External Interrupts */
    .word  isr_timer_0
    .word  isr_timer_1
    .word  isr_timer_2
    .word  isr_timer_3
    .word  isr_pwm_wrap
    .word  isr_usbctrl
    .word  isr_xip
    .word  isr_pio0_0
    .word  isr_pio0_1
    .word  isr_pio1_0
    .word  isr_pio1_1
    .word  isr_dma_0
    .word  isr_dma_1
    .word  isr_io_bank0
    .word  isr_io_qspi
    .word  isr_sio_proc0
    .word  isr_sio_proc1
    .word  isr_clocks
    .word  isr_spi0
    .word  isr_spi1
    .word  isr_uart0
    .word  isr_uart1
    .word  isr_adc_fifo
    .word  isr_i2c0
    .word  isr_i2c1
    .word  isr_rtc
.size  _vector, .-_vector

    .weak      isr_nmi
    .thumb_set isr_nmi, isr_default
    .weak      isr_hardfault
    .thumb_set isr_hardfault, isr_default
    .weak      isr_svcall
    .thumb_set isr_svcall, isr_default
    .weak      isr_pendsv
    .thumb_set isr_pendsv, isr_default
    .weak      isr_systick
    .thumb_set isr_systick, isr_default
    /* External Interrupts */
    .weak      isr_timer_0
    .thumb_set isr_timer_0, isr_default
    .weak      isr_timer_1
    .thumb_set isr_timer_1, isr_default
    .weak      isr_timer_2
    .thumb_set isr_timer_2, isr_default
    .weak      isr_timer_3
    .thumb_set isr_timer_3, isr_default
    .weak      isr_pwm_wrap
    .thumb_set isr_pwm_wrap, isr_default
    .weak      isr_usbctrl
    .thumb_set isr_usbctrl, isr_default
    .weak      isr_xip
    .thumb_set isr_xip, isr_default
    .weak      isr_pio0_0
    .thumb_set isr_pio0_0, isr_default
    .weak      isr_pio0_1
    .thumb_set isr_pio0_1, isr_default
    .weak      isr_pio1_0
    .thumb_set isr_pio1_0, isr_default
    .weak      isr_pio1_1
    .thumb_set isr_pio1_1, isr_default
    .weak      isr_dma_0
    .thumb_set isr_dma_0, isr_default
    .weak      isr_dma_1
    .thumb_set isr_dma_1, isr_default
    .weak      isr_io_bank0
    .thumb_set isr_io_bank0, isr_default
    .weak      isr_io_qspi
    .thumb_set isr_io_qspi, isr_default
    .weak      isr_sio_proc0
    .thumb_set isr_sio_proc0, isr_default
    .weak      isr_sio_proc1
    .thumb_set isr_sio_proc1, isr_default
    .weak      isr_clocks
    .thumb_set isr_clocks, isr_default
    .weak      isr_spi0
    .thumb_set isr_spi0, isr_default
    .weak      isr_spi1
    .thumb_set isr_spi1, isr_default
    .weak      isr_uart0
    .thumb_set isr_uart0, isr_default
    .weak      isr_uart1
    .thumb_set isr_uart1, isr_default
    .weak      isr_adc_fifo
    .thumb_set isr_adc_fifo, isr_default
    .weak      isr_i2c0
    .thumb_set isr_i2c0, isr_default
    .weak      isr_i2c1
    .thumb_set isr_i2c1, isr_default
    .weak      isr_rtc
    .thumb_set isr_rtc, isr_default
