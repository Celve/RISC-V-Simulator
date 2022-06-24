#include "instructions/j_ins.h"

#include <cstdio>
#include <iostream>

#include "common/utils.h"

namespace riscv {

void JIns::Init(u32 ins) {
  CalcImm(ins);
  rd_ = Get11To7(ins);
  ins_ = JInsType::JAL;
}

void JIns::CalcImm(u32 ins) {
  imm_ = Extend20(((ins >> 31 & 0x1) << 20) | ((ins >> 21 & 0x3FF) << 1) |
                  ((ins >> 20 & 0x1) << 11) | ((ins >> 12 & 0xFF) << 12));
}

void JIns::Execute() {
  u32 pc = regs_->GetPc();
  int imm = imm_;
  switch (ins_) {
    case JInsType::JAL:
      regs_->SetReg(rd_, pc + 4);
      regs_->SetPc(pc + imm);
      break;
  }
}

}  // namespace riscv
