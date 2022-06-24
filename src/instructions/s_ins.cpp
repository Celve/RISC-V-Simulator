#include "instructions/s_ins.h"

#include <cstdio>
#include <iostream>

#include "common/utils.h"

namespace riscv {

void SIns::Init(u32 ins) {
  CalcImm(ins);
  rs2_ = Get24To20(ins);
  rs1_ = Get19To15(ins);
  u32 part1 = Get14To12(ins);
  if (part1 == 0) {
    ins_ = SInsType::SB;
  } else if (part1 == 1) {
    ins_ = SInsType::SH;
  } else if (part1 == 2) {
    ins_ = SInsType::SW;
  } else {
    // TODO(celve): throw an error
  }
}

void SIns::CalcImm(u32 ins) { imm_ = Extend11(((ins >> 25 & 0x7F) << 5) | (ins >> 7 & 0x1F)); }

void SIns::Execute() {
  u32 reg1 = regs_->GetReg(rs1_);
  u32 reg2 = regs_->GetReg(rs2_);
  int imm = imm_;
  switch (ins_) {
    case SInsType::SB:
      // std::cout << "sb: " << rs1_ << " " << rs2_ << " " << reg1 + imm << std::endl;
      memory_->SetByte(reg1 + imm, reg2);
      break;
    case SInsType::SH:
      // std::cout << "sh: " << rs1_ << " " << rs2_ << " " << reg1 + imm << std::endl;
      memory_->SetHalf(reg1 + imm, reg2);
      break;
    case SInsType::SW:
      // std::cout << "sw: " << rs1_ << " " << rs2_ << " " << reg1 + imm << std::endl;
      memory_->SetWord(reg1 + imm, reg2);
      break;
  }
  regs_->IncreasePc(4);
}

}  // namespace riscv
