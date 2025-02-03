// All sizes in bytes

#include "slip.h"
namespace c_slip {
using ::Encapsulate;
using ::Deencapsulate;
using ::GetCapacity;
}

#include "slip.hpp"
#include "static_allocator.hpp"
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

/**
 * @brief Demonstrate API similarity between std::vector and static_vector
 * @note This shows an extremely dumbed down version of SLIP
 * @tparam Vec Vector type
 * @param vec Vector
 */
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
    print_heap_and_stack_info("--After performing some operation on the vector (pop_back)");
    vec.push_back(0xc0);
    vec.insert(vec.begin(), 0xc0);
    print_heap_and_stack_info("--After reframing");
    vec.clear();
    print_heap_and_stack_info("--After clearing");
}

/**
 * @brief Demonstrate SLIP in C++ using static_vector
 */
void slip_cpp() {
    static constexpr std::initializer_list<std::uint8_t> slip_msg_s = {1,2,3};
    static_vector<std::uint8_t, slip::GetCapacity(slip_msg_s.size())> slip_msg = slip_msg_s;
    print_bytes(slip_msg, "--Initial state");
    slip::Encapsulate(slip_msg);
    print_bytes(slip_msg, "--After encapsulation");
    static_cast<void>(slip::Deencapsulate(slip_msg));
    print_bytes(slip_msg, "--After deencapsulation");
}

/**
 * @brief Demonstrate SLIP in C using a fixed size buffer
 */
void slip_c() {
    auto c_print_bytes = [](const std::uint8_t* bytes, std::size_t size, const char* pre = "") {
        printf("%s\nBytes: ", pre);
        for (std::size_t i = 0; i < size; ++i) {
            printf("0x%02X ", bytes[i]);
        }
        printf("\n");
    };

    std::size_t c_slip_msg_size = 3;
    // Variable length array violates ISO C++ (ie. cannot use -pedantic)
    std::uint8_t c_slip_msg[c_slip::GetCapacity(c_slip_msg_size)] = {1,2,3};
    printf("C SLIP\n");
    c_slip::Encapsulate(c_slip_msg, &c_slip_msg_size);
    c_print_bytes(c_slip_msg, c_slip_msg_size, "--After encapsulation");
    (void)c_slip::Deencapsulate(c_slip_msg, &c_slip_msg_size);
    c_print_bytes(c_slip_msg, c_slip_msg_size, "--After deencapsulation");
}

int main() {
    static constexpr std::initializer_list<std::uint8_t> slip_msg = {0xC0,0x0D,0x0E,0x0A,0x0D,0x0B,0x0E,0x0E,0x0F,'\0', 0xC0};
    std::vector<std::uint8_t> heap_vec = slip_msg;
    static_vector<std::uint8_t, MAX_SLIP_MSG_SIZE> custom_svec = slip_msg;
    std::vector<std::uint8_t, static_allocator<std::uint8_t, MAX_SLIP_MSG_SIZE>> std_svec = slip_msg;
    printf("# Heap vector\n");
    show_api(heap_vec);
    printf("# Custom static vector\n");
    show_api(custom_svec);
    printf("# Std vector with static allocator\n");
    show_api(std_svec);
    slip_cpp();
    slip_c();
    return 0;
}
