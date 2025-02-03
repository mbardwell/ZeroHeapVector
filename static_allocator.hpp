#pragma once

#include <cstddef>
#include <cassert>

template <typename T, std::size_t Capacity>
class static_allocator {
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using void_pointer = void*;
    using const_void_pointer = const void*;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    template <typename U>
    struct rebind {
        using other = static_allocator<U, Capacity>;
    };

    static_allocator() = default;

    template <typename U>
    constexpr static_allocator(const static_allocator<U, Capacity>&) noexcept {}

    T* allocate(std::size_t n) {
        static_cast<void>(n);
        assert(n <= Capacity);
        return reinterpret_cast<T*>(buffer_);
    }

    void deallocate(T* p, std::size_t n) noexcept {
        static_cast<void>(p);
        static_cast<void>(n);
    }

    template <typename U>
    bool operator==(const static_allocator<U, Capacity>&) const noexcept {
        return true;
    }

    template <typename U>
    bool operator!=(const static_allocator<U, Capacity>&) const noexcept {
        return false;
    }

private:
    alignas(T) char buffer_[Capacity * sizeof(T)];
};
