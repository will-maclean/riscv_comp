# RISC-V Computer Emulator
_Will Maclean_

Let's build a RISC-V compliant emulator. Should be fun right?

## Example
We can run C programs (no standard library support). For example, the following
C program (found in `sample_c/sample_c.c`) can be build (using `sample_c/build.sh`)
and run with the emulator.

```c
#include "syscall.h"

void print_matrix(int m[3][3]){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            print_d(m[i][j]);
            if(j < 2){
                print_s(", ", 2);
            }
        }
        print_s("\n", 1);
    }
}

int main() {
    int x[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    print_matrix(x);

    return 0;
}
```

## The Computer
Basic information about this computer:
- 32bit memory addressing
- stack pointer starts at 0xFFFFFFEF
- no c standard library support
- basic custom syscalls
- supported instruction sets:
    - rv32i
    - rv32ic (in progress)
- stdout captured in `io_out.txt`

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
./build.sh [rv32i|rv32ic]
```

Note the the ELF file format is not currently supported - we compile into binary
format.

You can then rerun `build/riscv_comp sample_c/test.bin` (no rebuild required).
