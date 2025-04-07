#include "rv32c.hpp"
#include "instructions.hpp"
#include "utils.hpp"
#include "rv32i.hpp"


std::unique_ptr<AInstruction> rv32i_c0(RVUnparsedInstr unparsed_instr){
    if(unparsed_instr.type != RVUnparsedInstrType::INSTR16)
    {
        return std::make_unique<UndefInstr>(unparsed_instr);
    }
    const uint16_t instr = unparsed_instr.instr.instr_16;
    const uint16_t f3  = bits(instr, 13, 15);
    const uint16_t rs1 = bits(instr, 7, 9);
    const uint16_t rs2 = bits(instr, 2, 4);

    int32_t imm = 0;
    switch(f3){
        case 0x0:
            // c.addi4spn
            imm = 0;
            imm |= bit(instr, 5) << 3;
            imm |= bit(instr, 6) << 2;
            imm |= bits(instr, 7, 9) << 6;
            imm |= bits(instr, 11, 12) << 4;

            if (imm == 0){
                return std::make_unique<UndefInstr>(unparsed_instr);
            }

            return std::make_unique<ADDI>(2, imm, rs2+8, 2);

        case 0x2:
            // c.lw
            imm = 0;
            imm |= bit(instr, 5) << 6;
            imm |= bit(instr, 6) << 2;
            imm |= bits(instr, 10, 12) << 3;
            
            return std::make_unique<LOAD>(rs1+8, LoadType::LW, rs2+8, imm, 2);
        
        case 0x6:
            // c.sw
            imm = 0;
            imm |= bit(instr, 5) << 6;
            imm |= bit(instr, 6) << 2;
            imm |= bits(instr, 10, 12) << 3;

            return std::make_unique<STORE>(rs2+8, rs1+8, StoreType::SW, imm, 2);

        default:
            return std::make_unique<UndefInstr>(unparsed_instr);
    }

    return std::make_unique<UndefInstr>(unparsed_instr);
}
std::unique_ptr<AInstruction> rv32i_c1(RVUnparsedInstr unparsed_instr){
    if(unparsed_instr.type != RVUnparsedInstrType::INSTR16){
        return std::make_unique<UndefInstr>(unparsed_instr);
    }
    const uint16_t instr = unparsed_instr.instr.instr_16;
    const uint16_t f3 = bits(instr, 13, 15);
    const uint16_t f6 = bits(instr, 10, 15);

    // yucky immediate format unforunately
    int32_t immj = 0;
    immj |= bit(instr, 2) << 5;
    immj |= bits(instr, 3, 5) << 1;
    immj |= bit(instr, 6) << 7;
    immj |= bit(instr, 7) << 6;
    immj |= bit(instr, 8) << 10;
    immj |= bits(instr, 9, 10) << 8;
    immj |= bit(instr, 11) << 4;
    immj |= bit(instr, 12) << 11;
    immj = sext(immj, 11);

    const uint16_t rs1 = bits(instr, 7, 9);
    const uint16_t rs2 = bits(instr, 2, 4);
    const uint16_t rsd = bits(instr, 7, 11);
    int32_t immb = 0;
    immb |= bit(instr, 2) << 5;
    immb |= bits(instr, 3, 5) << 1;
    immb |= bits(instr, 5, 6) << 6;
    immb |= bits(instr, 10, 11) << 3;
    immb |= bit(instr, 12) << 8;

    int32_t imm = 0;
    switch(f3){
        case 0:
            // c.addi
            imm = 0;
            imm |= bits(instr, 2, 6);
            imm |= bit(instr, 12) << 5;
            imm = sext(imm, 5);

            if(rsd != 0 && imm == 0){
                return std::make_unique<UndefInstr>(unparsed_instr);
            }

            return std::make_unique<ADDI>(rsd, imm, rsd, 2);

        case 1:
            // c.jal
            return std::make_unique<JAL>(1, immj, 2);
        case 2:
            // c.li
            if(rsd == 0){
                // these are undefined
                return std::make_unique<UndefInstr>(unparsed_instr);
            }

            imm = 0;
            imm |= bits(instr, 2, 6);
            imm |= bit(instr, 12) << 5;
            imm = sext(imm, 5);

            return std::make_unique<ADDI>(0, imm, rsd, 2);

        case 3:
            // c.lui
            if(rsd == 0){
                return std::make_unique<UndefInstr>(unparsed_instr);
            } else if(rsd == 2){
                // c.addi16sp
                imm = 0;
                imm |= bit(instr, 2) << 5;
                imm |= bits(instr, 3, 4) << 7;
                imm |= bit(instr, 5) << 6;
                imm |= bit(instr, 6) << 4;
                imm |= bit(instr, 12) << 9;
                imm = sext(imm, 9);

                return std::make_unique<ADDI>(2, imm, 2, 2);
            }

            imm = 0;
            imm |= bits(instr, 2, 6);
            imm |= bit(instr, 12) << 5;
            imm <<= 12;
            imm = sext(imm, 17);

            return std::make_unique<ADDI>(rsd, imm, 0, 2);
        case 4:
            

            if(bits(instr, 10, 11) == 0){
                // shamt[5] must be 0 on rv32c
                if(bit(instr, 12)){
                    return std::make_unique<UndefInstr>(unparsed_instr);
                }
                // c.srli
                return std::make_unique<SRLI>(rs1+8, rs1+8, bits(instr, 2, 6), 2);
            } else if (bits(instr, 10, 11) == 1){
                // shamt[5] must be 0 on rv32c
                if(bit(instr, 12)){
                    return std::make_unique<UndefInstr>(unparsed_instr);
                }
                // c.srai
                return std::make_unique<SRAI>(rs1+8, rs1+8, bits(instr, 2, 6), 2);
            } else if (bits(instr, 10, 11) == 2){
                // c.andi
                imm = 0;
                imm |= bits(instr, 2, 6);
                imm |= bit(instr, 12) << 5;
                imm = sext(imm, 6);
                return std::make_unique<ANDI>(rs1+8, rs1+8, imm, 2);
            } else {
                switch (f6) {
                case 0x8F:
                    // c.and
                    return std::make_unique<AND>(rs1+8, rs2+8, rs1+8, 2);
                case 0x8E:
                    // c.or
                    return std::make_unique<OR>(rs1+8, rs2+8, rs1+8, 2);
                case 0x8D:
                    // c.xor
                    return std::make_unique<XOR>(rs1+8, rs2+8, rs1+8, 2);
                case 0x8C:
                    // c.sub
                    return std::make_unique<SUB>(rs1+8, rs2+8, rs1+8, 2);
                }
            }
        case 5:
            // c.j
            return std::make_unique<JAL>(0, immj, 2);
        case 6:
            // c.beqz
            return std::make_unique<BEQ>(rs1+8, 0, immb, 2);
        case 7:
            // c.bnez
            return std::make_unique<BNE>(rs1+8, 0, immb, 2);
        default:
            return std::make_unique<UndefInstr>(unparsed_instr);
    }

    return std::make_unique<UndefInstr>(unparsed_instr);
}
std::unique_ptr<AInstruction> rv32i_c2(const RVUnparsedInstr &unparsed_instr){
    if(unparsed_instr.type != RVUnparsedInstrType::INSTR16){
        return std::make_unique<UndefInstr>(unparsed_instr);
    }
    const uint16_t instr = unparsed_instr.instr.instr_16;
    const uint16_t f3  = bits(instr, 13, 15);
    const uint16_t f4  = bits(instr, 12, 15);
    const uint32_t rs2 = bits(instr,  2,  6);
    const uint32_t rd  = bits(instr,  7, 11);

    int32_t imm = 0;
    switch(f3){
        case 0x0:
            // c.slli
            if(rd == 0 || bit(instr, 12)){
                return std::make_unique<UndefInstr>(unparsed_instr);
            }
            imm = 0;
            imm |= bits(instr, 2, 6);

            return std::make_unique<SLLI>(rd, imm, rd, 2);
            
        case 0x2:
            // c.lwsp
            if(rd == 0){
                return std::make_unique<UndefInstr>(unparsed_instr);
            }

            imm = 0;
            imm |= bits(instr, 2, 3) << 6;
            imm |= bits(instr, 4, 6) << 2;
            imm |= bit(instr, 12)    << 5;

            return std::make_unique<LOAD>(2, LoadType::LW, rd, imm, 2);
        case 0x6:
            // c.swsp
            imm = 0;
            imm |= bits(instr, 7,  8) << 6;
            imm |= bits(instr, 9, 12) << 2;

            return std::make_unique<STORE>(rs2, 2, StoreType::SW, imm, 2);
        case 0x9:
            return std::make_unique<EBREAK>(2);
    }

    switch(f4){
        case 0x8:
            // c.jr
            if(rd == 0){
                return std::make_unique<UndefInstr>(unparsed_instr);
            }

            if(bits(instr, 2, 6) != 0){
                // c.mv
                return std::make_unique<ADD>(rs2, 0, rd, 2);
            }

            return std::make_unique<JALR>(rd, 0, 0, 2);
        case 0x9:
            if (rd == 0){
                // c.break
                return std::make_unique<EBREAK>(2);
            } else if(rs2 == 0){
                if(bits(instr, 2, 6) != 0){
                    // these are undefined
                    return std::make_unique<UndefInstr>(unparsed_instr);
                }

                // c.jalr
                return std::make_unique<JALR>(rd, 0, 1, 2);
            }
            // c.add
            return std::make_unique<ADD>(rs2, rd, rd, 2);
    }

    return std::make_unique<UndefInstr>(unparsed_instr);
}

std::unique_ptr<ISA> isa_rv32c(){
    std::unique_ptr<ISA> isa = std::make_unique<ISA>();

	isa.get()->add_instr(0x0, instr_gen(rv32i_c0));
	isa.get()->add_instr(0x1, instr_gen(rv32i_c1));
	isa.get()->add_instr(0x2, instr_gen(rv32i_c2));
    return isa;
}