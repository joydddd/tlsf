#include "tlsf.h"
#include "arena.h"
#include <iostream>
namespace tlsf {

template <class T>
class tlsf_allocator {
    private:
     tlsf_t tlsf_i;
     tlsf_internal::Arena arena;

    public:
     typedef size_t size_type;
     typedef ptrdiff_t difference_type;
     typedef T* pointer;
     typedef const T* const_pointer;
     typedef T& reference;
     typedef const T& const_reference;
     typedef T value_type;

     template <class U>
     struct rebind {
         typedef tlsf_allocator<U> other;
    };
    tlsf_allocator() throw() {
        tlsf_i = tlsf_create(arena.Alloc());
        tlsf_add_pool(tlsf_i, arena.Alloc(), tlsf_internal::PAGE_SIZE);
    }
    ~tlsf_allocator() throw() { tlsf_destroy(tlsf_i); }
    pointer allocate(size_type size, const void* hint = 0) throw(){
        pointer rt;
        rt = (pointer)tlsf_malloc(tlsf_i, size * sizeof(T));
        if (rt) return rt;
        std::cout << "TLSF Allocating new page" << std::endl;
        /* not enought pools, allocate new page */
        void* new_page = arena.Alloc();
        if (!new_page) {
            std::cerr << "Arena is full" << std::endl;
            return NULL; /* Arena is Full */
        }
        tlsf_add_pool(tlsf_i, new_page, tlsf_internal::PAGE_SIZE);
        return (pointer)tlsf_malloc(tlsf_i, size * sizeof(T));
    }
    void deallocate(pointer p, size_type n) throw() { tlsf_free(tlsf_i, p); }
    size_type max_size() const throw() { return tlsf_internal::PAGE_SIZE; }
};

// globals
template <class T, class U>
bool operator==(const tlsf_allocator<T>&, const tlsf_allocator<U>&) throw();
template <class T, class U>
bool operator!=(const tlsf_allocator<T>&, const tlsf_allocator<U>&) throw();

}  // namespace std