# ZeroHeapVector

_This was written for a talk. It is not production quality_.

Simple zero heap vector C++ implementation, focused on embedded systems. The advantages over `std::vector` are:

* Memory is allocated on the stack, which is generally faster than heap allocation
* Predictable Performance: Since the size is fixed, there is no need for dynamic memory allocation, leading to more predictable performance
* No Heap Fragmentation: As it does not use heap memory, it avoids issues related to heap fragmentation

If you are looking for a generic implementation, here are some great resources:

* Boost's static_vector
* Static vector open standard request [P0843r6](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/p0843r6.html)
* Watch [David Stone's CppCon talk](https://www.youtube.com/watch?v=I8QJLGI0GOE)

To run the example: install `g++ make`, compile with `make` and run the executable `./example{.exe}`. Optionally install `valgrind clang-tidy cppcheck` for static analysis and statistics.

This is written for C++14, but can fairly easily be modified for C++11. See the C++11 branch for details.

Terminology: `static_vector` == `stack_vector` == `zero heap vector`

## Key Results

Results are organized by commit they were derived from. Reverse chronological order.

### [b9af8fd](https://github.com/renode/renode/releases/tag/v1.15.1)  Out of bounds heap allocation on a microcontroller, bare metal

Show how easy it is to ask for more memory than is available when not checking at compile time.

This example is run using  with the following diff

```diff
diff --git a/renode/src/main.c b/renode/src/main.c
-  char data[] = "Hello World!";
+  print("Allocating memory");
+
+  int n_bytes = (256 * 1024) + 1;  // Whoops
+  char *l = (char *)(malloc(n_bytes));
+
+  if (l == NULL) {
+    fprintf(stderr, "Memory allocation failed\n");
+    return 1;
+}
+
+  char data[100];
+  (void)sprintf(data, "Address of l: %p, n_bytes: %d", (void*)l, n_bytes);
   print(data);
-
+  for (int i = 0; i < n_bytes; i++) {
+    l[i] = (char)(i % 256);
+  }
+  int random_index = rand() % n_bytes;
+  char random_char = l[random_index];
+  (void)sprintf(data, "Random char at index %p: %c", l + random_index, random_char);
+  print(data);
+
+  print("Freeing memory");
+  free(l);
```

We asked for +1 more than available SRAM. It runs fine

```shell
Allocating memory
Address of l: 0x200000b0, n_bytes: 262145
Random char at index 0x200000b0:
Freeing memory
```

Renode is courteous enough to warn us, but you would not know if you were running on a real target

```shell
16:43:30.0907 [WARNING] sysbus: [cpu: 0x8000290] WriteByte to non existing peripheral at 0x20040000, value 0x50.
```

### a21af68  Compile with no heap

Options:

* Some programs let you set heap to zero
* Overload `new`/`free` operators
* Redefine `malloc` ex. `#define malloc(dummy) NULL; _Static_assert(0, "Err: use of dynamic memory")`
* Redirect linker `g++ -Wl,--wrap=malloc`

```shell
$ g++ -g -Wl,--wrap=malloc -o example_malloc example_malloc.cpp
undefined reference to `__wrap_malloc'
```

### a21af68  Overload heap memory

```shell
$ docker run --rm -it --memory 100m -v $(pwd):/mnt ubuntu:24.04 bash  # Limit container memory to 100MB
$ make example_malloc
$ ./example_malloc 100000000
$ ./example_malloc 200000000  # Linux optimistic memory allocation magic? `top` VIRT 200MB, RES 80MB
$ ./example_malloc 300000000  # `top` VIRT 300MB, RES 100MB -> 💥
Killed
```

Prevent page swapping magic

```shell
$ docker run --rm  -it --memory 100m --memory-swappiness 0 -v $(pwd):/mnt ubuntu:24.04  # Limit container memory to 100MB
$ make example_malloc
$ ./example_malloc 100000000
$ ./example_malloc 100000100
$ ./example_malloc 100010000
$ ./example_malloc 101000000
Killed
```

Can also overload memory using emulators like renode ([STM43F4 example](https://medium.com/@pc0is0me/getting-started-with-stm32f4-emulation-using-renode-f6cb158d27d1))

```diff
$ git diff renode/src/main.c
diff --git a/renode/src/main.c b/renode/src/main.c
index d6daa24..c722f46 100644
--- a/renode/src/main.c
+++ b/renode/src/main.c
@@ -41,9 +41,20 @@ int main()
     CAN_Transmit(CAN1, &TxMsg);
     cnt++;
   }
-  char data[] = "Hello World!";
+  char data[] = "Allocating memory";
   print(data);
-
+
+  int n_bytes = 1000000;
+  char *l = (char *)(malloc(n_bytes));
+
+  for (int i = 0; i < n_bytes; i++) {
+    l[i] = (char)(i % 256);
+  }
+
+  char data2[] = "Freeing memory";
+  print(data2);
+  free(l);
+
   for (;;);

   return 0;
```



### 7b20a5b  Complete comm. protocol example

```shell
$ ./example.exe
--Initial state
Heap vector size: 11, capacity: 11
Stack vector size: 11, capacity: 128
0xC0 0x0D 0x0E 0x0A 0x0D 0x0B 0x0E 0x0E 0x0F 0x00 0xC0
--After unframing
Heap vector size: 9, capacity: 11
Stack vector size: 9, capacity: 128
0x0D 0x0E 0x0A 0x0D 0x0B 0x0E 0x0E 0x0F 0x00
--After removing delimiter
Heap vector size: 8, capacity: 11
Stack vector size: 8, capacity: 128
0x0D 0x0E 0x0A 0x0D 0x0B 0x0E 0x0E 0x0F
--After reframing
Heap vector size: 10, capacity: 11
Stack vector size: 10, capacity: 128
0xC0 0x0D 0x0E 0x0A 0x0D 0x0B 0x0E 0x0E 0x0F 0xC0
--After clearing
Heap vector size: 0, capacity: 11
Stack vector size: 0, capacity: 128
```

### c3b222c  Demonstrate simliarity between static_vector and std::vector APIs

`stack_vector` and std::vector APIs equivalency

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
