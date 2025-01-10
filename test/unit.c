#include "mm.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

// Test for _mm_malloc
void test_mm_malloc() {
    size_t size = 100;
    _mm_ptr_t ptr = _mm_malloc(size);
    assert(ptr != NULL);  // Ensure memory was allocated
    
    // Optionally, check if the memory can be used:
    *((int*)ptr) = 42;
    assert(*((int*)ptr) == 42);  // Check if value is correctly set

    _mm_free(ptr);  // Free the allocated memory
}

// Test for _mm_free
void test_mm_free() {
    size_t size = 100;
    _mm_ptr_t ptr = _mm_malloc(size);
    assert(ptr != NULL);  // Ensure memory was allocated

    _mm_free(ptr);  // Free the allocated memory

    // After freeing, the pointer should not be dereferenced or used, but we check here that no crash happens:
    // We rely on the allocator to properly handle this and not crash.
}

// Test for _mm_calloc
void test_mm_calloc() {
    size_t num = 10;
    size_t size = sizeof(int);
    _mm_ptr_t ptr = _mm_calloc(num, size);
    assert(ptr != NULL);  // Ensure memory was allocated
    
    // Check if memory is zeroed out
    for (size_t i = 0; i < num; i++) {
        assert(((int*)ptr)[i] == 0);  // Ensure each element is zero
    }

    _mm_free(ptr);  // Free the allocated memory
}

// Test for _mm_realloc
void test_mm_realloc() {
    size_t initial_size = 100;
    size_t new_size = 200;
    _mm_ptr_t ptr = _mm_malloc(initial_size);
    assert(ptr != NULL);  // Ensure memory was allocated

    // Set some values in the initial block
    *((int*)ptr) = 42;

    // Reallocate memory
    _mm_ptr_t new_ptr = _mm_realloc(ptr, new_size);
    assert(new_ptr != NULL);  // Ensure memory was reallocated

    // Check if the memory is still accessible
    assert(*((int*)new_ptr) == 42);  // Ensure value is retained after reallocation

    _mm_free(new_ptr);  // Free the allocated memory
}

// Test for _mm_alloca
void test_mm_alloca() {
    // Allocate memory on the stack using _mm_alloca
    size_t alloc_size = 256; // 256 bytes of stack space
    char *buffer = (char *)_mm_alloca(alloc_size);

    // Check that the pointer is not NULL
    assert(buffer != NULL);

    // Initialize the allocated memory
    for (size_t i = 0; i < alloc_size; i++) {
        buffer[i] = (char)(i % 256); // Fill with some pattern
    }

    // Verify the memory contents
    for (size_t i = 0; i < alloc_size; i++) {
        assert(buffer[i] == (char)(i % 256)); // Check if the pattern is correct
    }

    _mm_free(buffer);
}

int main() {
    // Run tests
    printf("Running tests...\n");

    test_mm_malloc();
    printf("test_mm_malloc:  passed.\n");

    test_mm_free();
    printf("test_mm_free  :  passed.\n");

    test_mm_calloc();
    printf("test_mm_calloc:  passed.\n");

    test_mm_realloc();
    printf("test_mm_realloc: passed.\n");

    test_mm_alloca();
    printf("test_mm_alloca:  passed.\n");

    printf("All tests is  :  passed!\n");

    return 0;
}