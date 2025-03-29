#define IO_ADDR 0xFFFFFFFE

void print_s(char* s, int len){
    for(int i = 0; i < len; i++){
        char c = s[i];

        __asm__ volatile (
            "addi t0, %1, 0\n"   // Load IO_ADDR into register t0
            "add t1, t0, %0\n"   // Calculate address: IO_ADDR + i, store in t1
            "sb %2, 0(t1)"       // Store byte: store c at address calculated in t1
            : // No outputs
            : "r" (i), "r" (IO_ADDR), "r" (c) // Inputs: i (for address offset), IO_ADDR, c (character)
            : "t0", "t1" // Clobbered registers
        );
    }
}

int main() {
    print_s("Hello there\n", 12);

    return 0;
}