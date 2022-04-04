#include <stddef.h>
#include <stdint.h>

namespace tlsf {
namespace tlsf_internal {

const size_t PAGE_SIZE = 4096;  // in bytes
const size_t MAX_PAGES = 1024;  // at most 4KB * 1024 = 4MB

class Arena {
    size_t pages_allocated;
    void* pages[MAX_PAGES];

    public:
     Arena();
     ~Arena();
     void* Alloc();
};

}  // namespace tlsf_internal
}  // namespace tlsf
