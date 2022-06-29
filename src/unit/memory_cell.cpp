#include "unit/memory_cell.h"

#include <iostream>

#include "common/utils.h"
#include "instruction/riscv_ins_type.h"
#include "storage/load_store_buffer.h"

namespace riscv {

bool MemoryCell::Load(LoadStoreBufferEntry &entry, u32 address, u32 &result) {
  entry.IncreaseCount(1);
  if (!entry.IsCompleted()) {
    return false;
  }
  auto ins = entry.GetIns().GetInsType();
  switch (ins) {
    case RiscvInsType::LB:
      result = Extend8(memory_->GetByte(address));
      return true;
    case RiscvInsType::LH:
      result = Extend16(memory_->GetHalf(address));
      return true;
    case RiscvInsType::LW:
      result = memory_->GetWord(address);
      return true;
    case RiscvInsType::LBU:
      result = memory_->GetByte(address);
      return true;
    case RiscvInsType::LHU:
      result = memory_->GetHalf(address);
      return true;
    default:
      return false;
  }
}

bool MemoryCell::Store(LoadStoreBufferEntry &entry, u32 address, u32 value) {
  entry.IncreaseCount(1);
  if (!entry.IsCompleted()) {
    return false;
  }
  auto ins = entry.GetIns().GetInsType();
  switch (ins) {
    case RiscvInsType::SB:
      memory_->SetByte(address, value);
      return true;
    case RiscvInsType::SH:
      memory_->SetHalf(address, value);
      return true;
    case RiscvInsType::SW:
      memory_->SetWord(address, value);
      return true;
    default:
      return false;
  }
}

}  // namespace riscv