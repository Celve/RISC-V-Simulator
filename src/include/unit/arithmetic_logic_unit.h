#pragma once
#include "instruction/riscv_ins.h"

namespace riscv {

class ArithmeticLogicUnit {
 public:
  u32 Execute(const RiscvInsType &type, u32 lhs, u32 rhs, u32 pc = 0U, u32 imm = 0U);
};

}  // namespace riscv