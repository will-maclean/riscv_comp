#define SYSCALL_CODE_ADDR 0xFFFFFFFF
#define SYSCALL_ARG1_ADDR 0xFFFFFFFE
#define SYSCALL_ARG2_ADDR 0xFFFFFFFD
#define SYSCALL_ARG3_ADDR 0xFFFFFFFC

void print_c(char c);
void print_s(char *s, int len);
void print_d(int d);

enum SYSCALL_CODE {
    SYSCALL_PRINT_C = 0u,
    SYSCALL_PRINT_D = 1u,
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