#include "tlsf.h"
#include "arena.h"
namespace tlsf {

template <class T>
class tlsf_allocator {
    private:
     tlsf_t tlsf;
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
    tlsf_allocator() throw();
    // tlsf_allocator(const tlsf_allocator&);

    // template <class U>
    // tlsf_allocator(const tlsf_allocator<U>&);

    // template <class U>
    // tlsf_allocator& operator=(const tlsf_allocator<U>&);

    ~tlsf_allocator() throw();
    // pointer address(reference) const;
    // const_pointer address(const_reference) const;
    pointer allocate(size_type, const void* hint = 0) throw();
    void deallocate(pointer p, size_type n) throw();
    size_type max_size() const throw();
};

// globals
template <class T, class U>
bool operator==(const tlsf_allocator<T>&, const tlsf_allocator<U>&) throw();
template <class T, class U>
bool operator!=(const tlsf_allocator<T>&, const tlsf_allocator<U>&) throw();

}  // namespace std