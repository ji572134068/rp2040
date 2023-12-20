#ifndef __HARDWARE_COMMON_H__
#define __HARDWARE_COMMON_H__

#include "reg.h"

#ifdef __cplusplus
extern "C" {
#endif

__attribute__ ((__always_inline__)) static inline void __sev(void) {
    __asm__ volatile ("sev");
}

__attribute__ ((__always_inline__)) static inline void __wfe(void) {
    __asm__ volatile ("wfe");
}

__attribute__ ((__always_inline__)) static inline void __wfi(void) {
    __asm__ volatile ("wfi");
}

__attribute__ ((__always_inline__)) static inline void __dmb(void) {
    __asm__ volatile ("dmb" : : : "memory");
}

__attribute__ ((__always_inline__)) static inline void __dsb(void) {
    __asm__ volatile ("dsb" : : : "memory");
}

__attribute__ ((__always_inline__)) static inline void __isb(void) {
    __asm__ volatile ("isb");
}

__attribute__ ((__always_inline__)) static inline void enable_interrupt(void) {
    __asm__ volatile ("cpsie i");
}

__attribute__ ((__always_inline__)) static inline void disable_interrupt(void) {
    __asm__ volatile ("cpsid i");
}

__attribute__ ((__always_inline__)) static inline uint32_t save_and_disable_interrupt(void) {
    uint32_t status;
    __asm__ volatile ("mrs %0, PRIMASK" : "=r" (status)::);
    __asm__ volatile ("cpsid i");
    return status;
}

__attribute__ ((__always_inline__)) static inline void restore_interrupt(uint32_t status) {
    __asm volatile ("msr PRIMASK, %0"::"r" (status) : );
}

#ifdef __cplusplus
}
#endif

#endif /* __HARDWARE_COMMON_H__ */
