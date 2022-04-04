#include "tlsf_lib.h"
#include "tlsf.h"
namespace tlsf{
template <class T>
tlsf_allocator<T>::tlsf_allocator()throw(){
    tlsf_create();
}

// template <class T>
// tlsf::tlsf_allocator<T>::tlsf_allocator(const tlsf_allocator&){
//     tlsf_create_with_pool()
// }

// template <class T, class U>
// tlsf::tlsf_allocator<T>::tlsf_allocator(const tlsf_allocator<U>&){

// } 

template <class T>
tlsf_allocator<T>::~tlsf_allocator()throw(){
    tlsf_destroy(tlsf);
}

template <class T>
tlsf_allocator<T>::pointer tlsf_allocator<T>::allocate(tlsf_allocator<T>::size_type size, const void* hint)throw() {
    pointer rt;
    rt = tlsf_malloc(tlsf, size * sizeof(T));
    if (rt) return rt;
    /* not enought pools, allocate new page */
    void* new_page = arena.Alloc();
    if (!new_page) return NULL; /* Arena is Full */
    tlsf_add_pool(tlsf, new_page, tlsf_internal::PAGE_SIZE);
    return tlsf_malloc(tlsf, size * sizeof(T));
}

template <class T>
void tlsf_allocator<T>::deallocate(pointer p, size_type n){
    tlsf_free(tlsf, p);
}

template <class T>
tlsf_allocator<T>::size_type tlsf_allocator<T>::max_size() const throw() {
    return tlsf_internal::PAGE_SIZE;
}

template <class T, class U>
bool operator==(const tlsf_allocator<T>&, const tlsf_allocator<U>&) throw();

}