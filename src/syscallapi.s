# _syscall_gnuc.s
# Asm: GNU Asessmbler (GAS)
# x86_64 or i386 system call APIs for use from C-like languages.
.section .text
#if defined(__x86_64__)
# x86_64 Variant
.global _inv_syscall_x86_64
_inv_syscall_x86_64:
    mov %rdi, %rax
    mov %rsi, %rdi
    mov %rdx, %rsi
    mov %rcx, %rdx
    mov %r8, %rcx
    mov %r9, %r8
    mov 8(%rsp), %r9
    syscall
    ret
# #endif
# #ifdef __i386__
#elif defined(__i386__)
# i386 Variant
.global _inv_syscall_i386
_inv_syscall_i386:
    mov 4(%esp), %eax
    mov 8(%esp), %ebx
    mov 12(%esp), %ecx
    mov 16(%esp), %edx
    mov 20(%esp), %esi
    mov 24(%esp), %edi
    mov 28(%esp), %ebp
	# int 0x80 is syscall on i386
    int $0x80
    ret
#endif