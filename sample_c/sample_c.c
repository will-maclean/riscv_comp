#define IO_ADDR 0xFFFFFFFF

void print_s(char* s, int len){
    for(int i = 0; i < len; i++){
        char c = s[i];

        __asm__ volatile (
            "addi t0, %0, 0\n"   // Load IO_ADDR into register t0
            "sb %1, 0(t0)"       // Store byte: store c at address calculated in t1
            : // No outputs
            : "r" (IO_ADDR), "r" (c) // IO_ADDR, c (character)
            : "t0" // Clobbered registers
        );
    }
}

int main() {
    print_s("Hello there\n", 12);

    return 0;
}