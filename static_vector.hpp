#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>

template <typename T, std::size_t Capacity>
class static_vector {
public:
    using iterator = typename std::array<T, Capacity>::iterator;
    using const_iterator = typename std::array<T, Capacity>::const_iterator;

    static_vector();
    static_vector(std::initializer_list<T> init);
    void push_back(const T& value);
    void pop_back();
    std::size_t size() const;
    static std::size_t capacity();
    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;
    bool empty() const;
    iterator erase(iterator index) noexcept;
    iterator insert(iterator index, T val) noexcept;
    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;
    void clear();

private:
    std::array<T, Capacity> data_;
    std::size_t size_;
};

template <typename T, std::size_t Capacity>
static_vector<T, Capacity>::static_vector() : data_(std::array<T, Capacity>()), size_(0) {}

template <typename T, std::size_t Capacity>
static_vector<T, Capacity>::static_vector(std::initializer_list<T> init) : data_(), size_(init.size()) {
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
std::size_t static_vector<T, Capacity>::size() const {
    return size_;
}

template <typename T, std::size_t Capacity>
std::size_t static_vector<T, Capacity>::capacity() {
    return Capacity;
}

template <typename T, std::size_t Capacity>
T& static_vector<T, Capacity>::operator[](std::size_t index) {
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
typename static_vector<T, Capacity>::iterator static_vector<T, Capacity>::erase(iterator index) noexcept {
    std::copy(index + 1, data_.begin() + size_, index);
    --size_;
    return data_.begin() + size_;
}

template <typename T, std::size_t Capacity>
typename static_vector<T, Capacity>::iterator static_vector<T, Capacity>::insert(iterator index, T val) noexcept {
    std::copy_backward(index, data_.begin() + size_, data_.begin() + size_ + 1);
    *index = val;
    ++size_;
    return index;
}

template <typename T, std::size_t Capacity>
typename static_vector<T, Capacity>::iterator static_vector<T, Capacity>::begin() noexcept {
    return data_.begin();
}

template <typename T, std::size_t Capacity>
typename static_vector<T, Capacity>::const_iterator static_vector<T, Capacity>::begin() const noexcept {
    return data_.begin();
}

template <typename T, std::size_t Capacity>
typename static_vector<T, Capacity>::iterator static_vector<T, Capacity>::end() noexcept {
    return data_.begin() + size_;
}

template <typename T, std::size_t Capacity>
typename static_vector<T, Capacity>::const_iterator static_vector<T, Capacity>::end() const noexcept {
    return data_.begin() + size_;
}

template <typename T, std::size_t Capacity>
void static_vector<T, Capacity>::clear() {
    size_ = 0;
}
