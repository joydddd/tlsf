#include "tlsf/arena.h"
#include <stdlib.h>
namespace tlsf {
namespace tlsf_internal {

Arena::Arena() { pages_allocated = 0; }

Arena::~Arena() {
    for (size_t i = 0; i < pages_allocated; i++) std::free(pages[i]);
}

void* Arena::Alloc() {
    if (pages_allocated >= MAX_PAGES) return NULL;
    void* new_page = std::malloc(PAGE_SIZE);
    pages[pages_allocated] = new_page;
    pages_allocated++;
    return new_page;
}

}  // namespace tlsf_internal
}  // namespace tlsf
