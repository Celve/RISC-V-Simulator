#include "instructions/jtype_ins.h"

#include <cstdio>

#include "common/utils.h"

namespace riscv {

void JTypeIns::Init(u32 ins) {
  CalcImm(ins);
  rd_ = Get11To7(ins);
  ins_ = JIns::JAL;
}

void JTypeIns::CalcImm(u32 ins) {
  imm_ = ((ins >> 31 & 0x1) << 20) | ((ins >> 21 & 0x3FF) << 1) | ((ins >> 20 & 0x1) << 11) |
         ((ins >> 12 & 0xFF) << 12);
}

void JTypeIns::Execute() {
  switch (ins_) {
    case JIns::JAL:
      break;
  }
}

}  // namespace riscv
