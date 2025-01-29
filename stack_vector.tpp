template <typename T, std::size_t Capacity>
constexpr stack_vector<T, Capacity>::stack_vector() : data_(std::array<T, Capacity>()), size_(0) {}

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
