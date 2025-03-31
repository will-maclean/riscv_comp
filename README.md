# RISC-V Computer Emulator
_Will Maclean_

Let's build a RISC-V compliant emulator. Should be fun right?

## Example
We can run C programs (no standard library support). For example, the following
C program (found in `sample_c/sample_c.c`) can be build (using `sample_c/build.sh`)
and run with the emulator.

```c

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
```

## The Computer
Basic information about this computer:
- 32bit memory addressing
- write char to 0xFFFFFFFF for stdout
- stack pointer starts at 0xFFFFFFEF
- no c standard library support

## Build instructions

```
mkdir build
cd build
cmake ..
make
```
## Custom C program
You can modify `sample_c/sample_c.c`. You can then build the runnable binary
with:

```
cd sample_c
./build.sh
```

Note the the ELF file format is not currently supported - we compile into binary
format.

You can then rerun `build/riscv_comp` (no rebuild required).