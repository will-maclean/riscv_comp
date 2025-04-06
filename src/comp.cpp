#include "comp.hpp"
#include <utils.hpp>

Comp::Comp(InstructionParser parser) :
    ram(RAM()),
    cpu(CPU(&this->ram, parser)){
        clear_stdout();
}

Comp::Comp(InstructionParser parser, std::string filename) :
    ram(RAM(filename)),
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