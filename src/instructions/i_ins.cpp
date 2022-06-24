#include "instructions/i_ins.h"

#include <atomic>
#include <iostream>

#include "common/utils.h"

namespace riscv {

void IIns::Init(u32 ins) {
  u32 part1 = Get31To25(ins);
  u32 shamt = Get24To20(ins);
  imm_ = Get31To20(ins);
  rs1_ = Get19To15(ins);
  u32 part2 = Get14To12(ins);
  rd_ = Get11To7(ins);
  u32 part3 = Get6To0(ins);

  IdentifyOp(part1, part2, part3, shamt);
  imm_ = Extend11(imm_);
}

void IIns::IdentifyOp(u32 part1, u32 part2, u32 part3, u32 shamt) {
  if (part2 == 0 && part3 == 103) {
    ins_ = IInsType::JALR;
  } else if (part2 == 0 && part3 == 3) {
    ins_ = IInsType::LB;
  } else if (part2 == 1 && part3 == 3) {
    ins_ = IInsType::LH;
  } else if (part2 == 2 && part3 == 3) {
    ins_ = IInsType::LW;
  } else if (part2 == 4 && part3 == 3) {
    ins_ = IInsType::LBU;
  } else if (part2 == 5 && part3 == 3) {
    ins_ = IInsType::LHU;
  } else if (part2 == 0 && part3 == 19) {
    ins_ = IInsType::ADDI;
  } else if (part2 == 2 && part3 == 19) {
    ins_ = IInsType::SLTI;
  } else if (part2 == 3 && part3 == 19) {
    ins_ = IInsType::SLTIU;
  } else if (part2 == 4 && part3 == 19) {
    ins_ = IInsType::XORI;
  } else if (part2 == 6 && part3 == 19) {
    ins_ = IInsType::ORI;
  } else if (part2 == 7 && part3 == 19) {
    ins_ = IInsType::ANDI;
  } else if (part1 == 0 && part2 == 1 && part3 == 19) {
    ins_ = IInsType::SLLI;
    imm_ = shamt;
  } else if (part1 == 0 && part2 == 5 && part3 == 19) {
    ins_ = IInsType::SRLI;
    imm_ = shamt;
  } else if (part1 == 32 && part2 == 5 && part3 == 19) {
    ins_ = IInsType::SRAI;
    imm_ = shamt;
  } else {
    // TODO(celve): the error
  }
}

void IIns::Execute() {
  u32 reg1 = regs_->GetReg(rs1_);
  int imm = Extend11(imm_);
  switch (ins_) {
    case IInsType::JALR:
      regs_->SetReg(rd_, regs_->GetPc() + 4);
      regs_->SetPc((reg1 + imm) & (~1));
      return;
    case IInsType::LB:
      regs_->SetReg(rd_, Extend8(memory_->GetByte(reg1 + imm)));
      break;
    case IInsType::LH:
      regs_->SetReg(rd_, Extend16(memory_->GetHalf(reg1 + imm)));
      break;
    case IInsType::LW:
      // std::cout << "lw: " << rs1_ << " " << rd_ << " " << reg1 + imm << std::endl;
      regs_->SetReg(rd_, memory_->GetWord(reg1 + imm));
      break;
    case IInsType::LBU:
      // std::cout << "lbu: " << rs1_ << " " << rd_ << " " << reg1 + imm << std::endl;
      regs_->SetReg(rd_, memory_->GetByte(reg1 + imm));
      break;
    case IInsType::LHU:
      regs_->SetReg(rd_, memory_->GetHalf(reg1 + imm));
      break;
    case IInsType::ADDI:
      regs_->SetReg(rd_, reg1 + imm);
      break;
    case IInsType::SLTI:
      regs_->SetReg(rd_, u32(int(reg1) < imm));
      break;
    case IInsType::SLTIU:
      regs_->SetReg(rd_, u32(reg1 < u32(imm)));
      break;
    case IInsType::XORI:
      regs_->SetReg(rd_, reg1 ^ imm);
      break;
    case IInsType::ORI:
      regs_->SetReg(rd_, reg1 | imm);
      break;
    case IInsType::ANDI:
      regs_->SetReg(rd_, reg1 & imm);
      break;
    case IInsType::SLLI:
      if ((imm >> 5 & 1) == 0) {
        regs_->SetReg(rd_, reg1 << imm);
      }
      break;
    case IInsType::SRLI:
      if ((imm >> 5 & 1) == 0) {
        regs_->SetReg(rd_, reg1 >> imm);
      }
      break;
    case IInsType::SRAI:
      if ((imm >> 5 & 1) == 0) {
        regs_->SetReg(rd_, int(reg1) >> imm);
      }
      break;
  }
  regs_->IncreasePc(4);
}

}  // namespace riscv
