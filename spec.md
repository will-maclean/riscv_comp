# RISC-V Computer Spec
The goal of this emulator is to run a user-compiled program. For this to work,
the funcionality of the emulator needs to be well defined. Hence, this document
will be the "source of truth" for implementation details - if the emulator code
is different to this spec, then the bug is with the emulator, not the spec.

## CPU architecture
Currently, this is a single-core, single thread hardware emulation. The goal
in the future is to add multi-core and multi-thread support.

## Memory Layout
32 bit byte addressable memory. The program binary is loaded into the start
of the memory, starting at address 0 (i.e., starting pc=`0x0`). By default, the 
loaded program is treated as ROM, meaning any attempted writes will cause a 
warning and no write. The stack pointer starts at `0xFFFFFFEF`.

## Supported Instruction Sets
This is a 32-bit emulator, so only the 32 bit ISAs (and 16 bit compressed ISAs)
are supported.

| ISA | Support Level |
| --- | ------------- |
| I | Supported |
| C | Supported |
| M | Planned |


## Syscalls
"Hardware" functionality is triggered with syscalls. Syscalls are triggered
with the `ecall` assembly instruction. The following memory addresses are 
relevant:

```c++
uint32_t SYSCALL_CODE_ADDR = 0xFFFFFFFF;    // Stores the syscall code
uint32_t SYSCALL_ARG1_ADDR = 0xFFFFFFFE;    // syscall arg1, byte
uint32_t SYSCALL_ARG2_ADDR = 0xFFFFFFFD;    // syscall arg2, byte
uint32_t SYSCALL_ARG3_ADDR = 0xFFFFFFF9;    // syscall arg3, word
```

The supported syscalls are documented below

### print_c
Prints a character to stdout.

| Arg | Description |
| - | - |
| Syscall code | 0 |
| Arg 1 | char to stdout |
| Arg 2 | N/A |
| Arg 3 | N/A |

### print_d
Prints an integer to stdout.

| Arg | Description |
| - | - |
| Syscall code | 1 |
| Arg 1 | integer to stdout |
| Arg 2 | N/A |
| Arg 3 | N/A |

### timer_configure
Configure a timer. On trigger, an interrupt is called at the interrupt address.

| Arg | Description |
| - | - |
| Syscall code | 2 |
| Arg 1 | lower 4 bits is the timer number, upper 4 bits is the timer call type |
| Arg 2 | number of ticks |
| Arg 3 | interrupt address |

Timer call types:
- 0: Configure
- 1: Deconfigure (in this case, Arg 2 and Arg 3 are ignored)

### exit_interrupt
Exits out of an interrupt, restoring the normal thread execution. If the 
application is not currently in an interrupt, this is equivalent to a `NOP`.

| Arg | Description |
| - | - |
| Syscall code | 3 |
| Arg 1 | N/A |
| Arg 2 | N/A |
| Arg 3 | N/A |

## Interrupts
Interrupts are implemented, but at a very simple level. Currently, only timers
trigger interrupts, although this is likely to change.

CPU threads and cores can be marked as non-interruptable. In this case, if an
interrupt is triggered, the interrupt is currently ignored (although output
will be logged showing this). This may change.

On an interrupt:
1. The current thread execution is halted
2. The PC is set to the interrupt address
3. Execution continues until the `exit_interrupt` syscall is called.

Note - at this stage interrupts are NOT responsible for saving and/or restoring
register state. This is likely to come in the future.