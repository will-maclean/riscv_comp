#include "comp.hpp"
#include "rv32i.hpp"

#include <iostream>

int main(){
	InstructionParser parser;
	parser.register_isa(isa_rv32i());

	Comp comp = Comp(parser);
	comp.start();

	return 0;
}
