#include "comp.hpp"

Comp::Comp(InstructionParser parser) :
    ram(RAM()),
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