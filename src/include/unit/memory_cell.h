#pragma once

#include "common/config.h"
#include "instruction/riscv_ins_type.h"
#include "storage/load_store_buffer.h"
#include "storage/memory.h"

namespace riscv {

class MemoryCell {
 public:
  explicit MemoryCell(Memory *memory) : memory_(memory) {
    address_read_ = address_write_ = 0;
    input_read_ = input_write_ = 0;
    output_read_ = output_write_ = 0;
    count_read_ = count_write_ = 0;
  }

  void Load(const RiscvInsType &ins, u32 address);
  void Store(const RiscvInsType &ins, u32 address, u32 value);

  void Execute();
  void Update();

  bool AlmostDone();
  bool IsCompleted();
  u32 GetValue();

 private:
  RiscvInsType ins_read_;
  RiscvInsType ins_write_;
  u8 count_read_;
  u8 count_write_;
  u32 address_read_;
  u32 address_write_;
  u32 input_read_;
  u32 input_write_;
  u32 output_read_;
  u32 output_write_;
  Memory *memory_;
};

}  // namespace riscv
