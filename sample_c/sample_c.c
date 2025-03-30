#define IO_ADDR 0xFFFFFFFF

void print_s(char* s, int len){
    for(int i = 0; i < len; i++){
        volatile char c = s[i];

        __asm__ volatile (
            "sb %1, 0(%0)"
            :
            : "r" (IO_ADDR), "r" (c)
            :
        );
    }
}

int main() {
    print_s("Hello there\n", 12);

    return 0;
}