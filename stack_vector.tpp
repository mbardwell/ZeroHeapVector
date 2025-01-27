template <typename T, std::size_t N>
stack_vector<T, N>::stack_vector() : data_(std::array<T, N>()), idx_(0) {}

template <typename T, std::size_t N>
void stack_vector<T, N>::push_back(const T& value) {
    data_[idx_++] = value;
}

template <typename T, std::size_t N>
void stack_vector<T, N>::pop_back() {
    --idx_;
}
