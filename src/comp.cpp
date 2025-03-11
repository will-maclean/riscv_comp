#include "comp.hpp"

Comp::Comp() :
    ram(RAM()),
    cpu(CPU(&this->ram)){
}