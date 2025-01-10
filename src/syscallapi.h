#if !defined(_SYSCALLAPI_H_LOADED)
#define _SYSCALLAPI_H_LOADED

/* size_t */
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__x86_64__)

#if !defined(__inv_syscall_x86_64_defined)
#define __inv_syscall_x86_64_defined

/**
 * @brief Invokes a system call with a variable number of arguments.
 *
 * This function is implemented in `syscall_gnuc.s` and provides
 * a low-level interface for making system calls.
 *
 * @param number The system call number.
 * @param ... The arguments for the system call (up to six arguments).
 * @return The result of the system call as a void* (use casting as needed).
 */
void *_inv_syscall_x86_64(size_t number, ...);

#endif // __inv_syscall_x86_64_defined

// #endif // __x86_64__

// if defined(__i386__)

#elif defined(__i386__)

#if !defined(__inv_syscall_i386_defined)
#define __inv_syscall_i386_defined

/**
 * @brief Invokes a system call with a variable number of arguments.
 *
 * This function is implemented in `syscall_gnuc.s` and provides
 * a low-level interface for making system calls.
 *
 * @param number The system call number.
 * @param ... The arguments for the system call (up to six arguments).
 * @return The result of the system call as a void* (use casting as needed).
 */
void *_inv_syscall_i386(size_t number, ...);

#endif // __inv_syscall_i386_defined

#endif // __i386__

#ifdef __cplusplus
}
#endif

#if defined(__x86_64__)
#define _inv_syscall _inv_syscall_x86_64
#elif defined(__i386__)
#define _inv_syscall _inv_syscall_i386
#endif // __x86_64__

#endif // _SYSCALLAPI_H_LOADED