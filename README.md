# ZeroHeapVector

Simple zero heap vector C++ implementation, focused on embedded systems. The advantages over `std::vector` are:

* Memory is allocated on the stack, which is generally faster than heap allocation.
* Predictable Performance: Since the size is fixed, there is no need for dynamic memory allocation, leading to more predictable performance.
* No Heap Fragmentation: As it does not use heap memory, it avoids issues related to heap fragmentation.

If you are looking for a generic implementation, here are some resources:

* Boost's static_vector
* Static vector open standard request [P0843r6](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/p0843r6.html)
* Watch [David Stone's CppCon talk](https://www.youtube.com/watch?v=I8QJLGI0GOE)

To run the example: install g++, compile with `make` and run the executable `./example{.exe}`. Optionally install valgrind, clang-tidy and cppcheck for static analysis and statistics.

Terminology: `static_vector` == `stack_vector` == `zero heap vector`

## Key Results

### c3b222c  Demonstrate simliarity between static_vector and std::vector APIs

`stack_vector` behaves as expected

```shell
CAPACITY=1024 make stats
$ ./example.exe
--Initial state
Heap vector size: 11, capacity: 11
Stack vector size: 11, capacity: 1024
--After unframing
Heap vector size: 9, capacity: 11
Stack vector size: 9, capacity: 1024
--After modifyng message by removing null byte
Heap vector size: 8, capacity: 11
Stack vector size: 8, capacity: 1024
0x0D 0x0E 0x0A 0x0D 0x0B 0x0E 0x0E 0x0F
0x0D 0x0E 0x0A 0x0D 0x0B 0x0E 0x0E 0x0F
--After performing operation
Heap vector size: 8, capacity: 11
Stack vector size: 8, capacity: 1024
--After clearing
Heap vector size: 0, capacity: 11
Stack vector size: 0, capacity: 1024
```
