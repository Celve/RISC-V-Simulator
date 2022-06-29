#include "unit/memory_cell.h"

#include <iostream>

#include "common/utils.h"
#include "instruction/riscv_ins_type.h"

namespace riscv {

u32 MemoryCell::Load(const RiscvInsType &ins, u32 address) {
  switch (ins) {
    case RiscvInsType::LB:
      return Extend8(memory_->GetByte(address));
    case RiscvInsType::LH:
      return Extend16(memory_->GetHalf(address));
    case RiscvInsType::LW:
      return memory_->GetWord(address);
    case RiscvInsType::LBU:
      return memory_->GetByte(address);
    case RiscvInsType::LHU:
      return memory_->GetHalf(address);
    default:
      return 0U;
  }
}

void MemoryCell::Store(const RiscvInsType &ins, u32 address, u32 value) {
  switch (ins) {
    case RiscvInsType::SB:
      memory_->SetByte(address, value);
      break;
    case RiscvInsType::SH:
      memory_->SetHalf(address, value);
      break;
    case RiscvInsType::SW:
      memory_->SetWord(address, value);
      break;
    default:
      break;
  }
}

}  // namespace riscv