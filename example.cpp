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

// Alias for static_vector with a fixed size.
// This will be more familiar to C++ developers.
template <typename T>
using vector = static_vector<T, Capacity>;

template <typename Vec>
void print_message(const Vec& vec) {
    for (const auto& byte : vec) {
        printf("0x%02X ", byte);
    }
    printf("\n");
}

void print_vector_info(const char* pre, const std::vector<std::uint8_t>& heap_vec, const vector<std::uint8_t>& stack_vec) {
    printf("%s\n", pre);
    printf("Heap vector size: %zu, capacity: %zu\n", heap_vec.size(), heap_vec.capacity());
    printf("Stack vector size: %zu, capacity: %zu\n", stack_vec.size(), stack_vec.capacity());
    print_message(heap_vec);
    print_message(stack_vec);
}

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

void test_communication_protocol() {
    const std::initializer_list<std::uint8_t> slip_msg = {0xc0,0x0D,0x0E,0x0A,0x0D,0x0B,0x0E,0x0E,0x0F,'\0', 0xc0};
    std::vector<std::uint8_t> heap_vec = slip_msg;
    vector<std::uint8_t> stack_vec = slip_msg;

    heap_vec.pop_back();
    stack_vec.pop_back();

    print_vector_info("--Initial state", heap_vec, stack_vec);

    unframe(heap_vec);
    unframe(stack_vec);
    print_vector_info("--After unframing", heap_vec, stack_vec);

    remove_delimiter(heap_vec);
    remove_delimiter(stack_vec);
    print_vector_info("--After removing delimiter", heap_vec, stack_vec);

    reframe(heap_vec);
    reframe(stack_vec);
    print_vector_info("--After reframing", heap_vec, stack_vec);

    clear_vector(heap_vec);
    clear_vector(stack_vec);
    print_vector_info("--After clearing", heap_vec, stack_vec);
}

int main() {
    test_communication_protocol();
    return 0;
}
