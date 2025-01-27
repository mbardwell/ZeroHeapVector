#include "stack_vector.hpp"
#include <cstddef>
#include <cstdint>
#include <cstdio>

#ifdef SIZE
constexpr std::size_t N = SIZE;
#else
constexpr std::size_t N = 128;
#endif

// Potentially more user friendly to define vector size once based off of processor stack size
template <typename T>
using vector = stack_vector<T, N>;

int main() {
    vector<std::uint8_t> vec;
    for (std::size_t i = 0; i < vec.capacity(); ++i) {
        vec.push_back(static_cast<std::uint8_t>(i));
        printf("%d ", vec[i]);
    }
    printf("\nStatic vector used: %zu / %zu capacity", vec.size(), vec.capacity());
    for (std::size_t i = 0; i < vec.capacity(); ++i) {
        vec.pop_back();
        printf("%d ", vec[i]);
    }
    printf("\n");
    return 0;
}
