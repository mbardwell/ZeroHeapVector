#pragma once

#include <array>
#include <cassert>
#include <cstddef>

template <typename T, std::size_t Capacity>
class static_vector {
public:
    using iterator = typename std::array<T, Capacity>::iterator;
    using const_iterator = typename std::array<T, Capacity>::const_iterator;

    static_vector();
    static_vector(const std::initializer_list<T> init);
    void push_back(const T& value);
    void pop_back();
    auto size() const;
    constexpr static auto capacity();
    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;
    bool empty() const;
    iterator erase(iterator index);
    iterator insert(iterator index, T val);
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
    void clear();

private:
    std::array<T, Capacity> data_;
    std::size_t size_;  // Number of active elements
};

template <typename T, std::size_t Capacity>
static_vector<T, Capacity>::static_vector() : data_(std::array<T, Capacity>()), size_(0) {}

template <typename T, std::size_t Capacity>
static_vector<T, Capacity>::static_vector(const std::initializer_list<T> init) : data_(), size_(init.size()) {
    assert(init.size() <= Capacity);
    std::copy(init.begin(), init.end(), data_.begin());
}

template <typename T, std::size_t Capacity>
void static_vector<T, Capacity>::push_back(const T& value) {
    assert(size_ < Capacity);
    data_[size_++] = value;
}

template <typename T, std::size_t Capacity>
void static_vector<T, Capacity>::pop_back() {
    if (!empty())
        --size_;
}

template <typename T, std::size_t Capacity>
auto static_vector<T, Capacity>::size() const {
    return size_;
}

template <typename T, std::size_t Capacity>
constexpr auto static_vector<T, Capacity>::capacity() {
    return Capacity;
}

template <typename T, std::size_t Capacity>
T& static_vector<T, Capacity>::operator[](std::size_t index) {
    size_ = size_ <= index ? index + 1 : size_;
    return data_[index];
}

template <typename T, std::size_t Capacity>
const T& static_vector<T, Capacity>::operator[](std::size_t index) const {
    return data_[index];
}

template <typename T, std::size_t Capacity>
bool static_vector<T, Capacity>::empty() const {
    return size_ == 0;
}

template <typename T, std::size_t Capacity>
typename static_vector<T, Capacity>::iterator static_vector<T, Capacity>::erase(iterator index) {
    std::copy(index + 1, data_.begin() + size_, index);
    --size_;
    return data_.begin() + size_;
}

template <typename T, std::size_t Capacity>
typename static_vector<T, Capacity>::iterator static_vector<T, Capacity>::insert(iterator index, T val) {
    std::copy_backward(index, data_.begin() + size_, data_.begin() + size_ + 1);
    *index = val;
    ++size_;
    return index;
}

template <typename T, std::size_t Capacity>
typename static_vector<T, Capacity>::iterator static_vector<T, Capacity>::begin() {
    return data_.begin();
}

template <typename T, std::size_t Capacity>
typename static_vector<T, Capacity>::const_iterator static_vector<T, Capacity>::begin() const {
    return data_.begin();
}

template <typename T, std::size_t Capacity>
typename static_vector<T, Capacity>::iterator static_vector<T, Capacity>::end() {
    return data_.begin() + size_;
}

template <typename T, std::size_t Capacity>
typename static_vector<T, Capacity>::const_iterator static_vector<T, Capacity>::end() const {
    return data_.begin() + size_;
}

template <typename T, std::size_t Capacity>
void static_vector<T, Capacity>::clear() {
    size_ = 0;
}
