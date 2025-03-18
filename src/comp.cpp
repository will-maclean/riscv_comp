#include "comp.hpp"

Comp::Comp(InstructionParser parser) :
    ram(RAM()),
    cpu(CPU(&this->ram, parser)){
}