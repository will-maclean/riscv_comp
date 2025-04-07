#include "comp.hpp"
#include "rv32i.hpp"
#include "rv32c.hpp"

#include <iostream>

int main(int argc, char *argv[]){
	// Get the filename to load
	std::string filename;
	if (argc < 2) {
		filename = "/home/will/code/riscv_comp/sample_c/test.bin";
	} else {
		filename = argv[1];
	}

	InstructionParser parser;
	parser.register_isa(isa_rv32i());
	parser.register_isa(isa_rv32c());

	Comp comp = Comp(parser, filename);
	comp.start();

	return 0;
}
