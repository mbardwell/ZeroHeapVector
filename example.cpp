#include "stack_vector.hpp"
#include <iostream>

int main() {
    stack_vector<int, 10> vec;
    std::cout << "Example program running.\n";
    for (int i = 0; i < 10; ++i) {
        vec.push_back(i);
        std::cout << "Stack vector using " << vec.size() << "/" << vec.capacity() << " capacity\n";
    }
    for (int i = 0; i < 10; ++i) {
        vec.pop_back();
        std::cout << "Stack vector using " << vec.size() << "/" << vec.capacity() << " capacity\n";
    }
    return 0;
}
