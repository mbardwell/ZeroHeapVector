#include "stack_vector.hpp"
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <initializer_list>
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

void test_communication_protocol() {
    const std::initializer_list<std::uint8_t> slip_msg = {0xc0,0x0D,0x0E,0x0A,0x0D,0x0B,0x0E,0x0E,0x0F,'\0', 0x00};
    std::vector<std::uint8_t> heap_vec = slip_msg;
    vector<std::uint8_t> stack_vec = slip_msg;

    auto print_vector_info = [&heap_vec, &stack_vec](const char* pre) {
        printf("%s\n", pre);
        printf("Heap vector size: %zu, capacity: %zu\n", heap_vec.size(), heap_vec.capacity());
        printf("Stack vector size: %zu, capacity: %zu\n", stack_vec.size(), stack_vec.capacity());
    };

    print_vector_info("--Initial state");

    heap_vec.pop_back();
    heap_vec.erase(heap_vec.begin());
    stack_vec.pop_back();
    stack_vec.erase(0);  // Intentional API change to allow simpler implementation
    print_vector_info("--After unframing");

    heap_vec.pop_back();
    stack_vec.pop_back();
    print_vector_info("--After modifyng message by removing null byte");

    for (auto byte : heap_vec) {
        printf("0x%02X ", byte);
    }
    printf("\n");
    for (auto byte : stack_vec) {
        printf("0x%02X ", byte);
    }
    printf("\n");
    print_vector_info("--After performing operation");

    heap_vec.clear();
    stack_vec.clear();
    print_vector_info("--After clearing");
}

int main() {
    test_communication_protocol();
    return 0;
}
