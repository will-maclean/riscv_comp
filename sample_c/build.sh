/opt/riscv/bin/riscv32-unknown-elf-gcc  sample_c.c -c -o sample_c.o -nostdlib -march=rv32i
/opt/riscv/bin/riscv32-unknown-elf-as -o _start.o _start.s -march=rv32i
/opt/riscv/bin/riscv32-unknown-elf-ld -o test.elf _start.o sample_c.o -T linker_script.ld
/opt/riscv/bin/riscv32-unknown-elf-objdump -d test.elf > test.elf.disasm