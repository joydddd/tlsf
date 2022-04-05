#include "tlsf_lib.h"
#include <cstdlib>

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
}