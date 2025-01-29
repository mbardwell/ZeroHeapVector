#include "stack_vector.hpp"
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

constexpr std::size_t DefaultCapacity = 128;

#ifdef CAPACITY
constexpr std::size_t Capacity = CAPACITY;
#else
constexpr std::size_t Capacity = DefaultCapacity;
#endif

// Alias for stack_vector with a fixed size.
// This will be more familiar to C++ developers.
template <typename T>
using vector = stack_vector<T, Capacity>;

void test_stack_vector() {
    vector<std::uint8_t> vec;
    while (vec.size() < vec.capacity())
        vec.push_back(static_cast<std::uint8_t>(rand() % 256));
    printf("Static vector used: %zu / %zu capacity\n", vec.size(), vec.capacity());
    while (!vec.empty())
        vec.pop_back();
}

void test_heap_vector() {
    std::vector<std::uint8_t> vec;
    while (vec.size() < vec.capacity())
        vec.push_back(static_cast<std::uint8_t>(rand() % 256));
    printf("Heap vector used: %zu / %zu capacity\n", vec.size(), vec.capacity());
    while (!vec.empty())
        vec.pop_back();
}

int main() {
    test_stack_vector();
    test_heap_vector();
    return 0;
}
