#include "instructions/u_ins.h"

#include <iostream>

#include "common/utils.h"

namespace riscv {

void UIns::Init(u32 ins) {
  imm_ = Get31To12(ins) << 12;
  rd_ = Get11To7(ins);
  u32 part1 = Get6To0(ins);
  IdentifyOp(part1);
}

void UIns::IdentifyOp(u32 part1) {
  if (part1 == 55) {
    ins_ = UInsType::LUI;
  } else if (part1 == 23) {
    ins_ = UInsType::AUIPC;
  } else {
    // TODO(celve): add throw
  }
}

void UIns::Execute() {
  switch (ins_) {
    case UInsType::LUI:
      regs_->SetReg(rd_, imm_);
      break;
    case UInsType::AUIPC:
      regs_->SetReg(rd_, regs_->GetPc() + imm_);
      break;
  }
  regs_->IncreasePc(4);
}

}  // namespace riscv