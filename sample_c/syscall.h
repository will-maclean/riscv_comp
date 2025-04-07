#define SYSCALL_CODE_ADDR 0xFFFFFFFF
#define SYSCALL_ARG1_ADDR 0xFFFFFFFE
#define SYSCALL_ARG2_ADDR 0xFFFFFFFD
#define SYSCALL_ARG3_ADDR 0xFFFFFFFC

#define uint8_t unsigned char
#define uint32_t unsigned int

void print_c(char c);
void print_s(char *s, int len);
void print_d(int d);

enum SYSCALL_CODE {
    SYSCALL_PRINT_C = 0u,
    SYSCALL_PRINT_D = 1u,
    SYSCALL_TIMER_CONFIGURE = 2u,
    SYSCALL_EXIT_INTERRUPT = 3u
};

enum TIMER_CALL_TYPE {
    TIMER_CONFIGURE = 0u,
    TIMER_DECONFIGURE = 1u,
};

void print_c(char c){
    __asm__ volatile (
        "sb %1, 0(%0)\n"
        "sb %3, 0(%2)\n"
        "ecall"
        :
        : "r" (SYSCALL_ARG1_ADDR), "r" (c), "r" (SYSCALL_CODE_ADDR), "r" (SYSCALL_PRINT_C)
        :
    );
}

void print_s(char* s, int len){
    for(int i = 0; i < len; i++){
        print_c(s[i]);
    }
}

void print_d(int d){
    __asm__ volatile (
        "sb %1, 0(%0)\n"
        "sb %3, 0(%2)\n"
        "ecall"
        :
        : "r" (SYSCALL_ARG1_ADDR), "r" (d), "r" (SYSCALL_CODE_ADDR), "r" (SYSCALL_PRINT_D)
        :
    );
}

void configure_timer_fn_ptr(
    uint8_t timer_id,
    TIMER_CALL_TYPE call_type,
    uint8_t timer_ticks,
    void* fn
){
    uint8_t arg1 = timer_id | call_type << 4;
    __asm__(
        "sb %1, 0(%0)\n"
        "sb %3, 0(%2)\n"
        "sw %5, 0(%4)\n"
        "ecall"
        :
        : "r" (SYSCALL_CODE_ADDR), "r" (SYSCALL_TIMER_CONFIGURE),
          "r" (SYSCALL_ARG1_ADDR), "r" (arg1),
          "r" (SYSCALL_ARG2_ADDR), "r" (timer_ticks),
          "r" (SYSCALL_ARG3_ADDR), "r" (fn)
        :
    );
}

void configure_timer_raw_interrupt_addr(
    uint8_t timer_id,
    TIMER_CALL_TYPE call_type,
    uint8_t timer_ticks,
    uint32_t interrupt_addr
){
    uint8_t arg1 = timer_id | call_type << 4;
    __asm__(
        "sb %1, 0(%0)\n"
        "sb %3, 0(%2)\n"
        "sw %5, 0(%4)\n"
        "ecall"
        :
        : "r" (SYSCALL_CODE_ADDR), "r" (SYSCALL_TIMER_CONFIGURE),
          "r" (SYSCALL_ARG1_ADDR), "r" (arg1),
          "r" (SYSCALL_ARG2_ADDR), "r" (timer_ticks),
          "r" (SYSCALL_ARG3_ADDR), "r" (interrupt_addr)
        :
    );
}

void exit_interrupt(){
    __asm__ (
        "sb %1, 0(%0)\n"
        "ecall"
        :
        : "r" (SYSCALL_CODE_ADDR), "r" (SYSCALL_EXIT_INTERRUPT)
        :
    );
}