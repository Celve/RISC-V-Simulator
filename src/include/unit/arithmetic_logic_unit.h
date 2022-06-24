#pragma once
#include "instruction/riscv_ins.h"

namespace riscv {

class ALU {
 public:
  u32 Execute(RiscvInsType type, u32 lhs, u32 rhs);
};

}  // namespace riscv