#include "instructions/utype_ins.h"

#include <iostream>

#include "common/utils.h"

namespace riscv {

void UTypeIns::Init(u32 ins) {
  imm_ = Get31To12(ins) << 12;
  rd_ = Get11To7(ins);
  u32 part1 = Get6To0(ins);
  IdentifyOp(part1);
}

void UTypeIns::IdentifyOp(u32 part1) {
  if (part1 == 55) {
    ins_ = UIns::LUI;
  } else if (part1 == 23) {
    ins_ = UIns::AUIPC;
  } else {
    // TODO(celve): add throw
  }
}

void UTypeIns::Execute() {
  switch (ins_) {
    case UIns::LUI:
      regs_->SetReg(rd_, imm_);
      break;
    case UIns::AUIPC:
      regs_->SetReg(rd_, regs_->GetPc() + imm_);
      break;
  }
  regs_->IncreasePc(4);
}

}  // namespace riscv