#pragma once

#include "common/config.h"
#include "instruction/riscv_ins_type.h"
#include "storage/memory.h"

namespace riscv {

class MemoryCell {
 public:
  explicit MemoryCell(Memory *memory) : memory_(memory) {}

  u32 Load(const RiscvInsType &ins, u32 address);
  void Store(const RiscvInsType &ins, u32 address, u32 value);

 private:
  Memory *memory_;
};

}  // namespace riscv
