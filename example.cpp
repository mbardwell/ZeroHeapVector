#include "stack_vector.hpp"
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

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
    while (vec.size() < vec.capacity())
        vec.push_back(static_cast<std::uint8_t>(rand() % 256));
    printf("Static vector used: %zu / %zu capacity", vec.size(), vec.capacity());
    while (!vec.empty())
        vec.pop_back();
    return 0;
}
