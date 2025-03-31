#include "comp.hpp"
#include <utils.hpp>

Comp::Comp(InstructionParser parser) :
    ram(RAM("/home/will/code/riscv_comp/sample_c/test.bin")),
    cpu(CPU(&this->ram, parser)){
        clear_stdout();
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