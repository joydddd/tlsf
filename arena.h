#include <stddef.h>
#include <stdint.h>

namespace tlsf {
namespace tlsf_internal {

const size_t PAGE_SIZE = 2097152;  // in bytes, 2MB huge pages if possible
const size_t MAX_PAGES = 1024;  // at most 2MB * 1024 = 2GB

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
