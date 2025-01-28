template <typename T, std::size_t N>
constexpr stack_vector<T, N>::stack_vector() : data_(std::array<T, N>()), idx_(0) {}

template <typename T, std::size_t N>
constexpr void stack_vector<T, N>::push_back(const T& value) {
    data_[idx_++] = value;
}

template <typename T, std::size_t N>
constexpr void stack_vector<T, N>::pop_back() {
    --idx_;
}

template <typename T, std::size_t N>
constexpr auto stack_vector<T, N>::size() const {
    return idx_;
}

template <typename T, std::size_t N>
constexpr auto stack_vector<T, N>::capacity() {
    return N;
}

template <typename T, std::size_t N>
constexpr T& stack_vector<T, N>::operator[](std::size_t index) {
    return data_[index];
}

template <typename T, std::size_t N>
constexpr const T& stack_vector<T, N>::operator[](std::size_t index) const {
    return data_[index];
}

template <typename T, std::size_t N>
constexpr bool stack_vector<T, N>::empty() const {
    return idx_ == 0;
}
