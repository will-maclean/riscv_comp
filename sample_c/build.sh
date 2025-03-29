../../xpack-riscv-none-elf-gcc-14.2.0-3/bin/riscv-none-elf-gcc  sample_c.c -c -o sample_c.o -nostdlib -march=rv32i
../../xpack-riscv-none-elf-gcc-14.2.0-3/bin/riscv-none-elf-as -o _start.o _start.s -march=rv32i
../../xpack-riscv-none-elf-gcc-14.2.0-3/bin/riscv-none-elf-ld -o test.elf _start.o sample_c.o