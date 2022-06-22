#include "instructions/itype_ins.h"

#include "common/utils.h"

namespace riscv {

void ITypeIns::Init(u32 ins) {
  u32 part1 = Get31To25(ins);
  u32 shamt = Get24To20(ins);
  imm_ = Get31To20(ins);
  rs1_ = Get19To15(ins);
  u32 part2 = Get14To12(ins);
  rd_ = Get11To7(ins);
  u32 part3 = Get6To0(ins);

  IdentifyOp(part1, part2, part3, shamt);
}

void ITypeIns::IdentifyOp(u32 part1, u32 part2, u32 part3, u32 shamt) {
  if (part2 == 0 && part3 == 103) {
    ins_ = IIns::JALR;
  } else if (part2 == 0 && part3 == 19) {
    ins_ = IIns::ADDI;
  } else if (part2 == 2 && part3 == 19) {
    ins_ = IIns::SLTI;
  } else if (part2 == 3 && part3 == 19) {
    ins_ = IIns::XORI;
  } else if (part2 == 4 && part3 == 19) {
    ins_ = IIns::ORI;
  } else if (part2 == 6 && part3 == 19) {
    ins_ = IIns::ANDI;
  } else if (part2 == 7 && part3 == 19) {
    ins_ = IIns::SLLi;
  } else if (part1 == 0 && part2 == 1 && part3 == 19) {
    ins_ = IIns::SLLI;
    imm_ = shamt;
  } else if (part1 == 0 && part2 == 5 && part3 == 19) {
    ins_ = IIns::SRLI;
    imm_ = shamt;
  } else if (part1 == 32 && part2 == 5 && part3 == 19) {
    ins_ = IIns::SRAI;
    imm_ = shamt;
  } else {
    // TODO(celve): the error
  }
}

void ITypeIns::Execute() {
  switch (ins_) {
    case IIns::JALR:
      break;
    case IIns::ADDI:
      break;
    case IIns::SLTI:
      break;
    case IIns::SRLI:
      break;
    case IIns::SRAI:
      break;
  }
}

}  // namespace riscv
