#include "syscall.hpp"
#include "consts.hpp"
#include "ram.hpp"

#include <iostream>

enum SYSCALL_CODE {
    SYSCALL_PRINT_C = 0u,
    SYSCALL_PRINT_D = 1u,
};

void syscall(RAM* ram);

void print_c(char c){
    std::cout << c;
}

void print_d(int d){
    std::cout << d;
}

void syscall(RAM* ram){
    uint8_t syscall_code = ram->get_b(SYSCALL_CODE_ADDR);
    uint8_t arg1 = ram->get_b(SYSCALL_ARG1_ADDR);
    uint8_t arg2 = ram->get_b(SYSCALL_ARG2_ADDR);
    uint8_t arg3 = ram->get_b(SYSCALL_ARG3_ADDR);

    switch (syscall_code) {
        case SYSCALL_PRINT_C:
            std::cout << "[SYSCALL] Print char: " << arg1 << std::endl;
            print_c(arg1);
            break;
        case SYSCALL_PRINT_D:
            std::cout << "[SYSCALL] Print int: " << arg1 << std::endl;
            print_d(arg1);
            break;
        default:
            std::cerr << "[SYSCALL] Unknown syscall code: " << (int)syscall_code << std::endl;
            break;
    }
}