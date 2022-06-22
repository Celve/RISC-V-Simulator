#include "instructions/itype_ins.h"

#include <atomic>
#include <iostream>

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
  } else if (part2 == 0 && part3 == 3) {
    ins_ = IIns::LB;
  } else if (part2 == 1 && part3 == 3) {
    ins_ = IIns::LH;
  } else if (part2 == 2 && part3 == 3) {
    ins_ = IIns::LW;
  } else if (part2 == 4 && part3 == 3) {
    ins_ = IIns::LBU;
  } else if (part2 == 5 && part3 == 3) {
    ins_ = IIns::LHU;
  } else if (part2 == 0 && part3 == 19) {
    ins_ = IIns::ADDI;
  } else if (part2 == 2 && part3 == 19) {
    ins_ = IIns::SLTI;
  } else if (part2 == 3 && part3 == 19) {
    ins_ = IIns::SLTIU;
  } else if (part2 == 4 && part3 == 19) {
    ins_ = IIns::XORI;
  } else if (part2 == 6 && part3 == 19) {
    ins_ = IIns::ORI;
  } else if (part2 == 7 && part3 == 19) {
    ins_ = IIns::ANDI;
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
  u32 reg1 = regs_->GetReg(rs1_);
  int imm = Extend11(imm_);
  switch (ins_) {
    case IIns::JALR:
      regs_->SetReg(rd_, regs_->GetPc() + 4);
      regs_->SetPc((reg1 + imm) & (~1));
      return;
    case IIns::LB:
      regs_->SetReg(rd_, Extend8(memory_->GetByte(reg1 + imm)));
      break;
    case IIns::LH:
      regs_->SetReg(rd_, Extend16(memory_->GetHalf(reg1 + imm)));
      break;
    case IIns::LW:
      // std::cout << "lw: " << rs1_ << " " << rd_ << " " << reg1 + imm << std::endl;
      regs_->SetReg(rd_, memory_->GetWord(reg1 + imm));
      break;
    case IIns::LBU:
      // std::cout << "lbu: " << rs1_ << " " << rd_ << " " << reg1 + imm << std::endl;
      regs_->SetReg(rd_, memory_->GetByte(reg1 + imm));
      break;
    case IIns::LHU:
      regs_->SetReg(rd_, memory_->GetHalf(reg1 + imm));
      break;
    case IIns::ADDI:
      regs_->SetReg(rd_, reg1 + imm);
      break;
    case IIns::SLTI:
      regs_->SetReg(rd_, u32(int(reg1) < imm));
      break;
    case IIns::SLTIU:
      regs_->SetReg(rd_, u32(reg1 < u32(imm)));
      break;
    case IIns::XORI:
      regs_->SetReg(rd_, reg1 ^ imm);
      break;
    case IIns::ORI:
      regs_->SetReg(rd_, reg1 | imm);
      break;
    case IIns::ANDI:
      regs_->SetReg(rd_, reg1 & imm);
      break;
    case IIns::SLLI:
      if ((imm >> 5 & 1) == 0) {
        regs_->SetReg(rd_, reg1 << imm);
      }
      break;
    case IIns::SRLI:
      if ((imm >> 5 & 1) == 0) {
        regs_->SetReg(rd_, reg1 >> imm);
      }
      break;
    case IIns::SRAI:
      if ((imm >> 5 & 1) == 0) {
        regs_->SetReg(rd_, int(reg1) >> imm);
      }
      break;
  }
  regs_->IncreasePc(4);
}

}  // namespace riscv
