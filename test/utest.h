#ifndef __EASYSTL_UTEST_H_
#define __EASYSTL_UTEST_H_

#include <functional>
#include <string>
#include <vector>

#include "vector_test.h"

//控制输出的颜色,并提供高亮选择
#define COLOR(msg, code) "\033[0;" #code "m" msg "\033[0m"
#define RED(msg) COLOR(msg, 31)
#define GREEN(msg) COLOR(msg, 32)
#define YELLOW(msg) COLOR(msg, 33)
#define BLUE(msg) COLOR(msg, 34)

class UTest {
    using test_func = std::function<void()>;

 public:
    static UTest &instance() {
        static UTest inst;
        return inst;
    }

 public:
    void register_test(const std::string &name, test_func func);
    void run();

 public:
    void add_succeed() { m_success_count++; }
    void add_failed() { m_fail_count++; }

 private:
    int m_success_count = 0;
    int m_fail_count = 0;
    std::vector<std::pair<std::string, test_func>> tests_;
};

#define TEST(name)                                               \
    void test_##name();                                          \
    class test_register_##name {                                 \
     public:                                                     \
        test_register_##name() {                                 \
            UTest::instance().register_test(#name, test_##name); \
        }                                                        \
    };                                                           \
    test_register_##name g_test_register_##name;                 \
    void test_##name()

#define RUN_ALL_TESTS() UTest::instance().run()

//比较的对象，需要重载<<、==、!=
#define EXCEPT_EQ(a, b)                                                                  \
    if ((a) != (b)) {                                                                    \
        std::cout << "│  ├──" << RED("Failed: ") << (a) << " != " << (b) << std::endl;   \
        UTest::instance().add_failed();                                                  \
    } else {                                                                             \
        std::cout << "│  ├──" << GREEN("Passed: ") << (a) << " == " << (b) << std::endl; \
        UTest::instance().add_succeed();                                                 \
    }

#endif // !__EASYSTL_UTEST_H_
