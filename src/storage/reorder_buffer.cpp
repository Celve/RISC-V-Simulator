#include "storage/reorder_buffer.h"

#include "instruction/riscv_general_type.h"
#include "instruction/riscv_ins.h"

namespace riscv {

ReorderBufferEntry::ReorderBufferEntry() {
  Init();
  ins_ = RiscvIns();
}

void ReorderBufferEntry::Init() {
  busy_ = false;
  state_ = TomasuloState::kUndefine;
  supposed_pc_ = INVALID_ADDRESS;
}

int ReorderBuffer::Push() {
  int index = entries_write_.Expand();
  if (index != INVALID_ENTRY) {
    Init(index);
  }
  return index;
}

bool ReorderBuffer::Pop() {
  int index = entries_write_.Front();
  if (!IsBusy(index)) {
    Init(index);
    entries_write_.PopFront();
    return true;
  }
  return false;
}

void ReorderBuffer::Update() { entries_read_ = entries_write_; }

void ReorderBuffer::Reset() {
  while (!entries_write_.Empty()) {
    entries_write_.PopBack();
  }
}

u32 ReorderBuffer::GetRelativeCount() {
  if (entries_read_.Empty()) {
    return 0;
  }
  int count = 0;
  int index = entries_read_.Front();
  entries_read_.Next(index);
  while (index != INVALID_ENTRY) {
    auto ins = entries_read_[index].GetIns();
    if (ins.GetGeneralType() == RiscvGeneralType::LType || ins.GetGeneralType() == RiscvGeneralType::SType) {
      ++count;
    } else if (ins.GetGeneralType() == RiscvGeneralType::JType) {
      return count;
    }
    entries_read_.Next(index);
  }
  return count;
}

}  // namespace riscv