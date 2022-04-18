#include "tlsf_lib.h"
#include "tlsf.h"

namespace tlsf{
tlsf_internal::Arena global_arena;
tlsf_t global_tlsf;

void global_init() {
    global_tlsf = tlsf_create(global_arena.Alloc());
    tlsf_add_pool(global_tlsf, global_arena.Alloc(), tlsf_internal::PAGE_SIZE);
}

void* malloc(size_t size) {
    if (global_tlsf == NULL) {
        // fprintf(stderr, "global_tlsf not initialized");
        global_init();
    }
    // fprintf(stderr, "using tlsf malloc size: %d\n", size);

    void* ptr = tlsf_malloc(global_tlsf, size);
    if (!ptr)
        tlsf_add_pool(global_tlsf, global_arena.Alloc(),
                      tlsf_internal::PAGE_SIZE);
    return tlsf_malloc(global_tlsf, size);
}

void* calloc(size_t num, size_t size) {
    void* ptr = malloc(num * size);
    if (!ptr) return ptr;
    for (size_t i = 0; i < num * size; i++) {
        ((uint8_t*)ptr)[i] = 0;
    }
    return ptr;
}

void* realloc(void* ptr, size_t new_size) {
    return tlsf_realloc(global_tlsf, ptr, new_size);
}

void free(void* ptr) { 
    // fprintf(stderr, "using tlsf free");
    tlsf_free(global_tlsf, ptr); }
}