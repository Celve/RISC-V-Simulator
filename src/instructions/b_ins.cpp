#include "instructions/b_ins.h"

#include <algorithm>
#include <iostream>

#include "common/utils.h"

namespace riscv {

void BIns::Init(u32 ins) {
  rs2_ = Get24To20(ins);
  rs1_ = Get19To15(ins);
  u32 part1 = Get14To12(ins);
  CalcImm(ins);
  IdentifyOp(part1);
}

void BIns::IdentifyOp(u32 part1) {
  if (part1 == 0) {
    ins_ = BInsType::BEQ;
  } else if (part1 == 1) {
    ins_ = BInsType::BNE;
  } else if (part1 == 4) {
    ins_ = BInsType::BLT;
  } else if (part1 == 5) {
    ins_ = BInsType::BGE;
  } else if (part1 == 6) {
    ins_ = BInsType::BLTU;
  } else if (part1 == 7) {
    ins_ = BInsType::BGEU;
  } else {
    // TODO(celve): add throw here
  }
}

void BIns::CalcImm(u32 ins) {
  imm_ = ((ins >> 31 & 0x1) << 12) | ((ins >> 25 & 0x3F) << 5) | ((ins >> 8 & 0xF) << 1) |
         ((ins >> 7 & 0x1) << 11);
}

void BIns::Execute() {
  int reg1 = regs_->GetReg(rs1_);
  int reg2 = regs_->GetReg(rs2_);
  int imm = Extend12(imm_);
  u32 pc = regs_->GetPc();
  switch (ins_) {
    case BInsType::BEQ:
      if (reg1 == reg2) {
        regs_->SetPc(pc + imm);
      } else {
        regs_->IncreasePc(4);
      }
      break;
    case BInsType::BNE:
      if (reg1 != reg2) {
        regs_->SetPc(pc + imm);
      } else {
        regs_->IncreasePc(4);
      }
      break;
    case BInsType::BLT:
      if (reg1 < reg2) {
        regs_->SetPc(pc + imm);
      } else {
        regs_->IncreasePc(4);
      }
      break;
    case BInsType::BGE:
      if (reg1 >= reg2) {
        regs_->SetPc(pc + imm);
      } else {
        regs_->IncreasePc(4);
      }
      break;
    case BInsType::BLTU:
      if (u32(reg1) < u32(reg2)) {
        regs_->SetPc(pc + imm);
      } else {
        regs_->IncreasePc(4);
      }
      break;
    case BInsType::BGEU:
      if (u32(reg1) >= u32(reg2)) {
        regs_->SetPc(pc + imm);
      } else {
        regs_->IncreasePc(4);
      }
      break;
  }
}

}  // namespace riscv
