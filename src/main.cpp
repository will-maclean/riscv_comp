#include "comp.hpp"
#include "rv32i.hpp"
#include "rv32c.hpp"

#include <iostream>

int main(int argc, char *argv[]){
	// Get the filename to load
	std::string filename;
	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
		return 1;
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
