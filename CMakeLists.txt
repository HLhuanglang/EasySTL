# 设置最低cmake版本,3.6-Morden CMake
cmake_minimum_required(VERSION 3.6)

# ---------------------------------------------------------------------------------------
# Start EasySTL project
# ---------------------------------------------------------------------------------------
# 项目名称-EasySTL
project(
  EasySTL
  VERSION 1.0.0
  LANGUAGES CXX)

# 导入GunDirs
include(GNUInstallDirs)

# ---------------------------------------------------------------------------------------
# Compiler config
# ---------------------------------------------------------------------------------------
# 指定cpp11标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# 生成compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 判断编译类型
if(CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Debug"))
  add_definitions("-DEASYSTL_DEBUG")
endif()

# ---------------------------------------------------------------------------------------
# config thrid_party
# ---------------------------------------------------------------------------------------
find_package(GTest 1.12.1 EXACT REQUIRED)
if(GTest_FOUND)
  message(STATUS "GTest found")
endif()

# ---------------------------------------------------------------------------------------
# EasySTL单元测试
# ---------------------------------------------------------------------------------------
file(GLOB_RECURSE EASYSTL_UNITTEST_SOURCES "${CMAKE_SOURCE_DIR}/test/*.cpp")
add_executable(EasySTLUnitTest ${EASYSTL_UNITTEST_SOURCES})
target_include_directories(EasySTLUnitTest PUBLIC ${CMAKE_SOURCE_DIR}/easystl)
target_link_libraries(EasySTLUnitTest GTest::gtest GTest::gtest_main)