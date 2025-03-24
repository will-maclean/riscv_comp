#include "comp.hpp"
#include "rv32i.hpp"

#include <iostream>

int main(){
	InstructionParser parser;
	std::unique_ptr<ISA> rv32i = isa_rv32i();
	parser.register_isa(isa_rv32i());
	Comp comp = Comp(parser);

	return 0;
}
