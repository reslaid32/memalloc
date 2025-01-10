/**
 * @file memalloc.h
 * @brief Header file for memory allocation API.
 */

#if !defined(_MM_H_LOADED)
#define _MM_H_LOADED

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#if !defined(MEMALLOC_EXPORTS)
#define MEMALLOC_EXPORTS
#if defined(MM_STATIC)
#define MEMALLOC_API
#else
#if defined(_WIN32)
#if defined(MEMALLOC_LIBRARY_BUILD)
#define MEMALLOC_API __declspec(dllexport)
#else
#define MEMALLOC_API __declspec(dllimport)
#endif // MEMALLOC_LIBRARY_BUILD
#else
#if defined(MEMALLOC_LIBRARY_BUILD)
#define MEMALLOC_API __attribute__((visibility("default")))
#else
#define MEMALLOC_API
#endif // MEMALLOC_LIBRARY_BUILD
#endif // _WIN32
#endif // MM_STATIC
#endif // MEMALLOC_EXPORTS

/**
 * @typedef _mm_ptr_t
 * @brief Data type representing a pointer to memory.
 * 
 * This type is used in all memory allocation, deallocation, and reallocation operations.
 */
typedef void *_mm_ptr_t, mm_ptr_t;

typedef struct MM_Block {
    size_t size;
    struct MM_Block *next;
    bool free;
} MM_Block;
#define MM_BLOCK_SIZE sizeof(MM_Block)

/**
 * @brief System call for controlling the heap break.
 * 
 * This system call adjusts the heap break. If the address is NULL, the function returns the current heap break.
 * 
 * @param addr The new heap break address. If addr is NULL, the current heap break is returned.
 * @return The new heap break address, or (void *)-1 on failure.
 */
MEMALLOC_API _mm_ptr_t  _mm_brk     (_mm_ptr_t  addr                );

/**
 * @brief Allocates memory on the stack.
 * 
 * This function allocates memory on the stack, which will be automatically freed when the function exits.
 * 
 * @param size The size of memory to allocate in bytes.
 * @return A pointer to the allocated memory or NULL on failure.
 */
MEMALLOC_API _mm_ptr_t  _mm_alloca  (size_t     size                );

/**
 * @brief Allocates memory from the heap.
 * 
 * This function allocates dynamic memory from the heap, using system calls to manage memory.
 * 
 * @param size The number of bytes to allocate.
 * @return A pointer to the allocated memory or NULL if allocation fails.
 */
MEMALLOC_API _mm_ptr_t  _mm_malloc  (size_t     size                );

/**
 * @brief Frees previously allocated memory.
 * 
 * This function marks a block of memory as free. The memory will be available for reuse in future allocations.
 * 
 * @param ptr A pointer to the block of memory to free. If ptr is NULL, nothing happens.
 */
MEMALLOC_API    void    _mm_free    (_mm_ptr_t  ptr                 );

/**
 * @brief Allocates and zeroes memory.
 * 
 * This function allocates memory for an array of objects and initializes all bytes to zero.
 * 
 * @param num The number of objects to allocate memory for.
 * @param size The size of each object in bytes.
 * @return A pointer to the allocated and zeroed memory or NULL if allocation fails.
 */
MEMALLOC_API _mm_ptr_t  _mm_calloc  (size_t     num,    size_t size );

/**
 * @brief Reallocates previously allocated memory.
 * 
 * This function changes the size of a previously allocated block of memory. If the new size is larger,
 * the function may allocate a new block and copy the data from the old block.
 * 
 * @param ptr A pointer to the previously allocated memory block.
 * @param size The new size of the memory block.
 * @return A pointer to the reallocated memory or NULL if the reallocation fails. If size is zero, 
 *         the behavior is the same as calling free().
 */
MEMALLOC_API _mm_ptr_t  _mm_realloc (_mm_ptr_t  ptr,    size_t size );

#endif // _MM_H_LOADED
