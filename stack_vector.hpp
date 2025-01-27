#pragma once

#include <cstddef>

template <typename T, std::size_t N>
class stack_vector {
public:
    stack_vector();
    void push_back(const T& value);
    void pop_back();

private:
    T data_[N];
    std::size_t idx_;
};

#include "stack_vector.tpp"
