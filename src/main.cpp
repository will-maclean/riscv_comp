#include "comp.hpp"
#include "rv32i.hpp"
#include "rv32c.hpp"

#include <iostream>

int main(){
	InstructionParser parser;
	parser.register_isa(isa_rv32i());
	parser.register_isa(isa_rv32c());

	Comp comp = Comp(parser);
	comp.start();

	return 0;
}
