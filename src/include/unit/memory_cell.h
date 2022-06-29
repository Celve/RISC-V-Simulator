#pragma once

#include "common/config.h"
#include "instruction/riscv_ins_type.h"
#include "storage/load_store_buffer.h"
#include "storage/memory.h"

namespace riscv {

class MemoryCell {
 public:
  explicit MemoryCell(Memory *memory) : memory_(memory) {}

  bool Load(LoadStoreBufferEntry &entry, u32 address, u32 &result);
  bool Store(LoadStoreBufferEntry &entry, u32 address, u32 value);

 private:
  Memory *memory_;
};

}  // namespace riscv
