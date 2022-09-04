# EasySTL

## 简介

stl库的简易化实现

## 项目结构

- compile_env：存放构建工具
  - windows：使用vs2022可直接打开工程项目
    - stl：存放源码
    - stl_test：编写的测试代码
  - linux：makefile
- docs：文档说明，一些常见的stl问题
- src：源码
- test：测试代码
- [bin]：存放编译后的文件

## 项目运行

### windows

进行compile_env/windows目录，使用vs2022打开msvc_stl.sln即可

### linux

进入compile_env/linux目录，执行make即可

## 实现说明

只关注容器和算法本身实现，其他辅助工具一律使用std.(其实std里面有些模板功能，我们无法用c++自举的，只能依赖编译器的实现...)