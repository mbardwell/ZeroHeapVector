#pragma once

#include <array>
#include <cstddef>

template <typename T, std::size_t N>
class stack_vector {
public:
    stack_vector();
    void push_back(const T& value);
    void pop_back();
    std::size_t size() const { return idx_; }
    static std::size_t capacity() { return N; }
    T& operator[](std::size_t index) {
        return data_[index];
    }
    const T& operator[](std::size_t index) const {
        return data_[index];
    }
    bool empty() const { return idx_ == 0; }

private:
    std::array<T, N> data_;
    std::size_t idx_;
};

#include "stack_vector.tpp"
