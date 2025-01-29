#pragma once

#include <array>
#include <cstddef>

template <typename T, std::size_t Capacity>
class stack_vector {
public:
    constexpr stack_vector();
    constexpr stack_vector(std::initializer_list<T> init);
    constexpr void push_back(const T& value);
    constexpr void pop_back();
    constexpr auto size() const;
    constexpr static auto capacity();
    constexpr T& operator[](std::size_t index);
    constexpr const T& operator[](std::size_t index) const;
    constexpr bool empty() const;
    constexpr void erase(std::size_t index);
    constexpr auto begin() const;
    constexpr auto end() const;
    constexpr void clear();

private:
    std::array<T, Capacity> data_;
    std::size_t size_;
};

template <typename T, std::size_t Capacity>
constexpr stack_vector<T, Capacity>::stack_vector() : data_(std::array<T, Capacity>()), size_(0) {}

template <typename T, std::size_t Capacity>
constexpr stack_vector<T, Capacity>::stack_vector(std::initializer_list<T> init) : data_(), size_(init.size()) {
    std::copy(init.begin(), init.end(), data_.begin());
}

template <typename T, std::size_t Capacity>
constexpr void stack_vector<T, Capacity>::push_back(const T& value) {
    data_[size_++] = value;
}

template <typename T, std::size_t Capacity>
constexpr void stack_vector<T, Capacity>::pop_back() {
    --size_;
}

template <typename T, std::size_t Capacity>
constexpr auto stack_vector<T, Capacity>::size() const {
    return size_;
}

template <typename T, std::size_t Capacity>
constexpr auto stack_vector<T, Capacity>::capacity() {
    return Capacity;
}

template <typename T, std::size_t Capacity>
constexpr T& stack_vector<T, Capacity>::operator[](std::size_t index) {
    return data_[index];
}

template <typename T, std::size_t Capacity>
constexpr const T& stack_vector<T, Capacity>::operator[](std::size_t index) const {
    return data_[index];
}

template <typename T, std::size_t Capacity>
constexpr bool stack_vector<T, Capacity>::empty() const {
    return size_ == 0;
}

template <typename T, std::size_t Capacity>
constexpr void stack_vector<T, Capacity>::erase(std::size_t index) {
    if (index < size_) {
        std::move(data_.begin() + index + 1, data_.begin() + size_, data_.begin() + index);
        --size_;
    }
}

template <typename T, std::size_t Capacity>
constexpr auto stack_vector<T, Capacity>::begin() const {
    return data_.begin();
}

template <typename T, std::size_t Capacity>
constexpr auto stack_vector<T, Capacity>::end() const {
    return data_.begin() + size_;
}

template <typename T, std::size_t Capacity>
constexpr void stack_vector<T, Capacity>::clear() {
    size_ = 0;
}
