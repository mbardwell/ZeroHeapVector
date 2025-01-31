#include "static_vector.hpp"
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

template <typename Vec>
void unframe(Vec& vec) {
    vec.pop_back();
    vec.erase(vec.begin());
}

template <typename Vec>
void remove_delimiter(Vec& vec) {
    vec.pop_back();
}

template <typename Vec>
void clear_vector(Vec& vec) {
    vec.clear();
}

template <typename Vec>
void reframe(Vec& vec) {
    vec.push_back(0xc0);
    vec.insert(vec.begin(), 0xc0);
}

void test_slip_small() {
    const std::initializer_list<std::uint8_t> slip_msg = {0xc0,0x0D,0x0E,0x0A,0x0D,0x0B,0x0E,0x0E,0x0F,'\0', 0xc0};
    std::vector<std::uint8_t> heap_vec = slip_msg;
    static_vector<std::uint8_t, Capacity> stack_vec = slip_msg;

    auto print_vector_info = [&heap_vec, &stack_vec](const char* pre) {
        printf("%s\n", pre);
        printf("Heap vector size: %zu, capacity: %zu\n", heap_vec.size(), heap_vec.capacity());
        printf("Stack vector size: %zu, capacity: %zu\n", stack_vec.size(), stack_vec.capacity());
        for (const auto& byte : heap_vec) {  // Or stack vector, they are the same
            printf("0x%02X ", byte);
        }
        printf("\n");
    };

    print_vector_info("--Initial state");

    unframe(heap_vec);
    unframe(stack_vec);
    print_vector_info("--After unframing");

    remove_delimiter(heap_vec);
    remove_delimiter(stack_vec);
    print_vector_info("--After removing delimiter");

    reframe(heap_vec);
    reframe(stack_vec);
    print_vector_info("--After reframing");

    clear_vector(heap_vec);
    clear_vector(stack_vec);
    print_vector_info("--After clearing");
}

void test_slip_large() {}

int main() {
    test_slip_small();
    test_slip_large();
    return 0;
}
