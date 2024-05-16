
创建容器的时候可以指定内存分配器，如果不指定则用默认的，指定的内存分配器需要实现allocator中定义的staic方法【编译时多态】

```cpp
#include <iostream>

template <typename T>
class DefaultAllocator {
 public:
    static void alloc() {
        std::cout << "Default!" << std::endl;
    }
};

template <typename T>
class HelloAllocator {
 public:
    static void alloc() {
        std::cout << "Hello!" << std::endl;
    }
};

template <typename T, typename Allocator = DefaultAllocator<T>>
class Test {
 public:
    using AllocatorType = Allocator;

 public:
    void test(const AllocatorType &Allocator = AllocatorType()) {
        Allocator.alloc();
    }
};

int main() {
    Test<int> t;
    t.test();
}
```