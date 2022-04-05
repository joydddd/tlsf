#include "tlsf/arena.h"
#include <sys/mman.h>
#include <stdlib.h>
#include <iostream>
#define MAP_HUGE_2MB (21 << MAP_HUGE_SHIFT)
namespace tlsf {
namespace tlsf_internal {

Arena::Arena() { pages_allocated = 0; }

Arena::~Arena() {
    for (size_t i = 0; i < pages_allocated; i++) {
        munmap(pages[i], PAGE_SIZE);
    }
}

void* Arena::Alloc() {
    if (pages_allocated >= MAX_PAGES) return NULL;
    void* new_page = nullptr;
    new_page =
        mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_HUGE_2MB, -1, 0);
    if (new_page == MAP_FAILED)
        std::cerr << "Alloc huge page failed" << std::endl;
    pages[pages_allocated] = new_page;
    pages_allocated++;
    return new_page;
}

}  // namespace tlsf_internal
}  // namespace tlsf
