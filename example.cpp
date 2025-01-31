// All sizes in bytes

#include "slip.hpp"
#include "static_vector.hpp"
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <initializer_list>
#include <vector>

constexpr std::size_t STM32F030F4_STACK_SIZE = 1024;

// Application specific. The less we use the better.
#ifndef CAPACITY
constexpr std::size_t MAX_SLIP_MSG_SIZE = STM32F030F4_STACK_SIZE / 2;
#else
constexpr std::size_t MAX_SLIP_MSG_SIZE = CAPACITY / 2;
#endif

template <typename Seq>
void print_bytes(Seq& s, const char* pre = "") {
    printf("%s\nBytes: ", pre);
    for (const auto& byte : s) {
        printf("0x%02X ", byte);
    }
    printf("\n");
}

template <typename Vec>
void show_api(Vec vec) {
    auto print_heap_and_stack_info = [&](const char* pre) {
        print_bytes(vec, pre); // or stack vec. They are the same
        printf("Vector size: %zu, capacity: %zu\n", vec.size(), vec.capacity());
    };

    print_heap_and_stack_info("--Initial state");
    vec.pop_back();
    vec.erase(vec.begin());
    print_heap_and_stack_info("--After unframing");
    vec.pop_back();
    print_heap_and_stack_info("--After removing delimiter");
    vec.push_back(0xc0);
    vec.insert(vec.begin(), 0xc0);
    print_heap_and_stack_info("--After reframing");
    vec.clear();
    print_heap_and_stack_info("--After clearing");
}

void show_slip() {
    static constexpr std::initializer_list<std::uint8_t> slip_msg_s = {1,2,3};
    static_vector<std::uint8_t, slip::GetCapacity(slip_msg_s.size())> slip_msg = slip_msg_s;
    print_bytes(slip_msg, "--Initial state");
    slip::encapsulate(slip_msg);
    print_bytes(slip_msg, "--After encapsulation");
    slip::deencapsulate(slip_msg);
    print_bytes(slip_msg, "--After deencapsulation");
}

int main() {
    static constexpr std::initializer_list<std::uint8_t> slip_msg = {0xc0,0x0D,0x0E,0x0A,0x0D,0x0B,0x0E,0x0E,0x0F,'\0', 0xc0};
    std::vector<std::uint8_t> heap_vec = slip_msg;
    static_vector<std::uint8_t, MAX_SLIP_MSG_SIZE> stack_vec = slip_msg;
    printf("# Heap vector\n");
    show_api(heap_vec);
    printf("# Stack vector\n");
    show_api(stack_vec);
    show_slip();
    return 0;
}
