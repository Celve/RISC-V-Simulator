#include "instructions/btype_ins.h"

#include "common/utils.h"

namespace riscv {

void BTypeIns::Init(u32 ins) {
  rs2_ = Get24To20(ins);
  rs1_ = Get19To15(ins);
  u32 part1 = Get14To12(ins);
  CalcImm(ins);
  IdentifyOp(part1);
}

void BTypeIns::IdentifyOp(u32 part1) {
  if (part1 == 0) {
    ins_ = BIns::BEQ;
  } else if (part1 == 1) {
    ins_ = BIns::BNE;
  } else if (part1 == 4) {
    ins_ = BIns::BLT;
  } else if (part1 == 5) {
    ins_ = BIns::BGE;
  } else if (part1 == 6) {
    ins_ = BIns::BLTU;
  } else if (part1 == 7) {
    ins_ = BIns::BGEU;
  } else {
    // TODO(celve): add throw here
  }
}

void BTypeIns::CalcImm(u32 ins) {
  imm_ = ((ins >> 31 & 1) << 12) + ((ins >> 25 & 0x3f) << 5) + ((ins >> 8 & 0xf) << 1) +
         ((ins >> 7 & 1) << 11);
}

void BTypeIns::Execute() {
  int reg1 = regs_->GetReg(rs1_);
  int reg2 = regs_->GetReg(rs2_);
  int imm = imm_;
  switch (ins_) {
    case BIns::BEQ:
      if (reg1 == reg2) {
        regs_->SetPc(imm);
      }
      break;
    case BIns::BNE:
      if (reg1 != reg2) {
        regs_->SetPc(imm);
      }
      break;
    case BIns::BLT:
      if (reg1 <= reg2) {
        regs_->SetPc(imm);
      }
      break;
    case BIns::BGE:
      if (reg1 >= reg2) {
        regs_->SetPc(imm);
      }
      break;
    case BIns::BLTU:
      if (u32(reg1) <= u32(reg2)) {
        regs_->SetPc(imm);
      }
      break;
    case BIns::BGEU:
      if (u32(reg1) >= u32(reg2)) {
        regs_->SetPc(imm);
      }
      break;
  }
}

}  // namespace riscv
