#include "unit/memory_cell.h"

#include <iostream>

#include "common/utils.h"
#include "instruction/riscv_ins_type.h"
#include "storage/load_store_buffer.h"

namespace riscv {

void MemoryCell::Load(const RiscvInsType &ins, u32 address) {
  count_read_ = 0;
  ins_write_ = ins;
  address_write_ = address;
}

void MemoryCell::Store(const RiscvInsType &ins, u32 address, u32 value) {
  count_read_ = 0;
  ins_write_ = ins;
  address_write_ = address;
  input_write_ = value;
}

void MemoryCell::Execute() {
  if (count_read_ == 3) {
    return;
  }
  count_write_ = count_read_ + 1;
  if (count_write_ != 3) {
    return;
  }
  switch (ins_read_) {
    case RiscvInsType::LB:
      output_write_ = Extend8(memory_->GetByte(address_read_));
      break;
    case RiscvInsType::LH:
      output_write_ = Extend16(memory_->GetHalf(address_read_));
      break;
    case RiscvInsType::LW:
      output_write_ = memory_->GetWord(address_read_);
      break;
    case RiscvInsType::LBU:
      output_write_ = memory_->GetByte(address_read_);
      break;
    case RiscvInsType::LHU:
      output_write_ = memory_->GetHalf(address_read_);
      break;
    case RiscvInsType::SB:
      memory_->SetByte(address_read_, input_read_);
      break;
    case RiscvInsType::SH:
      memory_->SetHalf(address_read_, input_read_);
      break;
    case RiscvInsType::SW:
      memory_->SetWord(address_read_, input_read_);
      break;
    default:
      break;
  }
}

void MemoryCell::Update() {
  ins_read_ = ins_write_;
  address_read_ = address_write_;
  output_read_ = output_write_;
  input_read_ = input_write_;
  count_read_ = count_write_;
}

bool MemoryCell::IsCompleted() { return count_read_ == 3; }

bool MemoryCell::AlmostDone() { return count_read_ == 2; }

u32 MemoryCell::GetValue() { return output_read_; }

}  // namespace riscv