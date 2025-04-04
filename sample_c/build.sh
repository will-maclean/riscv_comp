supported_archs=(
    "rv32i"
    "rv32ic"
)

if [[ ! " ${supported_archs[@]} " =~ " $1 " ]]; then
    echo "Error: Unsupported architecture '$1'. Supported architectures are: ${supported_archs[*]}"
    exit 1
fi

/opt/riscv/bin/riscv32-unknown-elf-gcc  sample_c.c -c -o sample_c.o -nostdlib -march=$1 -mabi=ilp32
/opt/riscv/bin/riscv32-unknown-elf-as -o _start.o _start.s -march=$1
/opt/riscv/bin/riscv32-unknown-elf-ld -o test.elf _start.o sample_c.o -T linker_script.ld
/opt/riscv/bin/riscv32-unknown-elf-objcopy -O binary test.elf test.bin
/opt/riscv/bin/riscv32-unknown-elf-objdump -D test.elf > test.elf.disasm
/opt/riscv/bin/riscv32-unknown-elf-objdump -b binary -m riscv:rv32 -D test.bin > test.bin.disasm