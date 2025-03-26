cmake_minimum_required(VERSION 3.30)
set(CMAKE_CXX_STANDARD 17)

project(riscv_comp)

include_directories(include)

add_library(riscv_comp_lib
    src/comp.cpp
    src/cpu.cpp
    src/instructions.cpp
    src/ram.cpp
    src/rv32i.cpp
)

add_executable(
    riscv_comp

    src/main.cpp
)

target_link_libraries(riscv_comp riscv_comp_lib)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.12.1 
)

FetchContent_MakeAvailable(googletest)

add_executable(test_riscv_comp
    tests/test_cpu.cpp
    tests/test_ram.cpp
    tests/test_utils.cpp
)

target_link_libraries(test_riscv_comp gtest gtest_main riscv_comp_lib)

enable_testing()
add_test(NAME riscv_comp_tests COMMAND test_riscv_comp)
