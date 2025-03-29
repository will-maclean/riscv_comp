#include "comp.hpp"

Comp::Comp(InstructionParser parser) :
    ram(RAM("/home/will/code/riscv_comp/sample_c/test.elf")),
    cpu(CPU(&this->ram, parser)){
}

void Comp::start(){
    this->cpu.start();
}

RAM* Comp::get_ram(){
    return &this->ram;
}
CPU* Comp::get_cpu(){
    return &this->cpu;
}