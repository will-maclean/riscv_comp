#pragma once

#include <cstdint>
#include <string>

const uint32_t N_TIMERS = 4;

const std::string IO_OUT_FILE = "io_out.txt";
constexpr uint32_t DEFAULT_START_PC = 0x0;
constexpr uint32_t DEFAULT_START_SP = 0xFFFFFFEF;

constexpr uint32_t SYSCALL_CODE_ADDR = 0xFFFFFFFF;
constexpr uint32_t SYSCALL_ARG1_ADDR = 0xFFFFFFFE;
constexpr uint32_t SYSCALL_ARG2_ADDR = 0xFFFFFFFD;
constexpr uint32_t SYSCALL_ARG3_ADDR = 0xFFFFFFF9;