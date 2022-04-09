#include "tlsf_lib.h"
#include <cstdlib>
#include <iostream>

int main() { 
    tlsf::tlsf_allocator<int> Allocator;
    int* array1 = Allocator.allocate(100);
    int* array2 = Allocator.allocate(200);
    for (size_t i = 0; i < 100; i++){
        array1[i] = i;
    }

    for (size_t j = 0; j < 200; j++){
        array2[j] = j;
    }

    for (size_t i = 0; i < 100; i++) {
        if (array1[i] != i) exit(1);
    }
    for (size_t j = 0; j < 200; j++) {
        if (array2[j] !=j) exit(1);
    }

    Allocator.deallocate(array1, 100);
    Allocator.deallocate(array2, 200);
    // std::cout << "check" << std::endl;

    /* alloc and free interface */
    tlsf::global_init();
    // std::cout << "init finish" << std::endl;
    int* vec1 = (int*)tlsf::malloc(100 * sizeof(int));
    // std::cout << "vec addr " << (long unsigned int)vec1 << std::endl;
    for (int i = 0; i < 100; i++) {
        vec1[i] = i;
    }
    for (int i = 0; i < 100;i++){
        if (vec1[i] != i) exit(1);
    }

    tlsf::free(vec1);
}