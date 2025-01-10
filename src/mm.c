
#include "mm.h"

#include "syscallapi.h"
#if defined(__x86_64__)
#include "_x86_64_syscalls.h"
#elif defined(__i386__)
#include "_i386_syscalls.h"
#endif // __x86_64__

#include <stdio.h>

#if !defined(NULL)
#if defined(__cplusplus)
#define NULL (0)
#else
#define NULL ((void*)0)
#endif // __cplusplus
#endif // NULL

_mm_ptr_t _mm_brk(_mm_ptr_t addr) {
    return _inv_syscall(SYS_BRK, addr);
}

static MM_Block *free_list        =  NULL;

_mm_ptr_t _mm_alloca(size_t size) {
    if (size == 0) return NULL;

    _mm_ptr_t current_stack_ptr = _mm_brk(NULL);
    _mm_ptr_t new_stack_ptr = current_stack_ptr - size;

    return new_stack_ptr;
}

_mm_ptr_t _mm_malloc(size_t size) {
    MM_Block *block;

    if (size <= 0) return NULL;

    if (!free_list) {
        void *heap_start = _mm_brk(NULL);
        void *new_brk = _mm_brk(heap_start + size + MM_BLOCK_SIZE);

        if (new_brk == (void *)-1) return NULL;

        block = (MM_Block *)heap_start;
        block->size = size;
        block->next = NULL;
        block->free = false;

        free_list = block;
    } else {
        MM_Block *current = free_list;
        while (current) {
            if (current->free && current->size >= size) {
                current->free = false;
                return (void *)(current + 1);
            }
            current = current->next;
        }

        void *heap_start = _mm_brk(NULL);
        void *new_brk = _mm_brk(heap_start + size + MM_BLOCK_SIZE);

        if (new_brk == (void *)-1) return NULL;

        block = (MM_Block *)heap_start;
        block->size = size;
        block->next = NULL;
        block->free = false;

        MM_Block *last = free_list;
        while (last->next) last = last->next;
        last->next = block;
    }

    return (void *)(block + 1);}

void _mm_free(_mm_ptr_t ptr) {
    if (!ptr) return;

    MM_Block *block = (MM_Block *)ptr - 1;

    for (size_t i = 0; i < block->size; i++) {
        ((char *)ptr)[i] = 0;
    }

    block->free = true;
}

_mm_ptr_t _mm_calloc(size_t num, size_t size) {
    size_t total_size = num * size;
    _mm_ptr_t ptr = _mm_malloc(total_size);

    if (ptr) {
        for (size_t i = 0; i < total_size; i++) {
            ((char *)ptr)[i] = 0;
        }
    }

    return ptr;
}

_mm_ptr_t _mm_realloc(_mm_ptr_t ptr, size_t size) {
    if (!ptr) {
        return _mm_malloc(size);
    }

    if (size == 0) {
        _mm_free(ptr);
        return NULL;
    }

    MM_Block *block = (MM_Block *)ptr - 1;

    if (block->size >= size) {
        return ptr;
    }

    _mm_ptr_t new_ptr = _mm_malloc(size);
    if (!new_ptr) return NULL;

    size_t copy_size = block->size < size ? block->size : size;
    for (size_t i = 0; i < copy_size; i++) {
        ((char *)new_ptr)[i] = ((char *)ptr)[i];
    }

    _mm_free(ptr);

    return new_ptr;
}