cmake_minimum_required(VERSION 3.30)
set(CMAKE_CXX_STANDARD 11)

project(riscv_comp)

include_directories(include)

add_executable(
    riscv_comp

    src/main.cpp
    src/comp.cpp
    src/cpu.cpp
    src/instructions.cpp
    src/ram.cpp

    include/comp.hpp
    include/cpu.hpp
    include/instructions.hpp
    include/ram.hpp
)
