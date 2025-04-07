#include "syscall.hpp"
#include "consts.hpp"
#include "ram.hpp"
#include "utils.hpp"

#include <iostream>
#include <compdevices.hpp>

enum SYSCALL_CODE {
    SYSCALL_PRINT_C = 0u,
    SYSCALL_PRINT_D = 1u,
    SYSCALL_TIMER_CONFIGURE = 2u,
};

void syscall(RAM* ram, CompDevices* devices);

void print_c(char c){
    write_to_stdout(std::string(1, c));
}

void print_d(int d){
    write_to_stdout(std::to_string(d));
}

enum TIMER_CALL_TYPE {
    TIMER_CONFIGURE = 0u,
    TIMER_DECONFIGURE = 1u,
};

void timer_configure(uint8_t arg1, uint8_t arg2, uint32_t arg3, CompDevices* devices){
    // 8 times
    // lower 4 bits of arg1 is the timer number
    // upper 4 bits of arg1 is the timer call type
    // arg2 is the number of ticks
    // arg3 is the interrupt address
    uint8_t timer_num = arg1 & 0x0F;
    uint8_t timer_call_type = (arg1 >> 4) & 0x0F;
    switch(timer_call_type){
        case TIMER_CONFIGURE:
            if (timer_num < N_TIMERS) {
                devices->timers[timer_num].configure(arg2, arg3);
                std::cout << "[TIMER] Configured timer " << timer_num << " with " << arg2 << " ticks and interrupt address " << arg3 << std::endl;
            } else {
                std::cerr << "[TIMER] Invalid timer number: " << timer_num << std::endl;
            }
            break;
        
        case TIMER_DECONFIGURE:
            if (timer_num < N_TIMERS) {
                devices->timers[timer_num].deconfigure();
                std::cout << "[TIMER] Deconfigured timer " << timer_num << std::endl;
            } else {
                std::cerr << "[TIMER] Invalid timer number: " << timer_num << std::endl;
            }
            break;

        default:
            break;
    }
}

void syscall(RAM* ram, CompDevices* devices){
    uint8_t syscall_code = ram->get_b(SYSCALL_CODE_ADDR);
    uint8_t arg1 = ram->get_b(SYSCALL_ARG1_ADDR);
    uint8_t arg2 = ram->get_b(SYSCALL_ARG2_ADDR);
    uint32_t arg3 = ram->get_w(SYSCALL_ARG3_ADDR);

    switch (syscall_code) {
        case SYSCALL_PRINT_C:
            std::cout << "[SYSCALL] print_c" << std::endl;
            print_c(arg1);
            break;
        case SYSCALL_PRINT_D:
            std::cout << "[SYSCALL] print_d" << std::endl;
            print_d(arg1);
            break;
        case SYSCALL_TIMER_CONFIGURE:
            std::cout << "[SYSCALL] timer_configure" << std::endl;
            timer_configure(arg1, arg2, arg3, devices);
            break;
        default:
            std::cerr << "[SYSCALL] Unknown syscall code: " << syscall_code << std::endl;
            break;
    }
}