#ifndef VECTOR_UTILS
#define VECTOR_UTILS
#include <iostream> 
#include <vector>

// Function to print vector 
template <typename T>
void print_vector(std::vector<T> v) {
    for (auto x : v) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

#endif
