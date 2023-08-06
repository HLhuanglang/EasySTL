#include "utest.h"
#include <iostream>

void UTest::register_test(const std::string &name, test_func func) {
    tests_.push_back(std::make_pair(name, func));
}

void UTest::run() {
    //输出开始执行测试的信息
    std::cout << "┌───────────────────────────────────────────────────────────────────────────────┐" << std::endl;
    std::cout << "│\t\t\t   " << BLUE("Begin to run all tests") << std::endl;
    std::cout << "├───────────────────────────────────────────────────────────────────────────────┤" << std::endl;

    for (auto const &it : tests_) {
        std::cout << "├──" << YELLOW("BeginTest: ") << it.first << std::endl;
        it.second();
        std::cout << "│  └" << YELLOW("END") << std::endl;
    }
    //输出测试结果
    std::cout << "├───────────────────────────────────────────────────────────────────────────────┐" << std::endl;
    std::cout << "│\tTotal: " << m_success_count + m_fail_count << "\t│"
              << GREEN("\tSucceed: ") << m_success_count << "\t│" << RED("\tFailed: ") << m_fail_count << std::endl;
    std::cout << "└───────────────────────────────────────────────────────────────────────────────┘" << std::endl;
}