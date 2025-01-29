#pragma once

#include <array>
#include <cstddef>

template <typename T, std::size_t Capacity>
class stack_vector {
public:
    constexpr stack_vector();
    constexpr void push_back(const T& value);
    constexpr void pop_back();
    constexpr auto size() const;
    constexpr static auto capacity();
    constexpr T& operator[](std::size_t index);
    constexpr const T& operator[](std::size_t index) const;
    constexpr bool empty() const;

private:
    std::array<T, Capacity> data_;
    std::size_t size_;
};

#include "stack_vector.tpp"
