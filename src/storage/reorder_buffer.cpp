#include "storage/reorder_buffer.h"

#include <iostream>

#include "common/config.h"
#include "instruction/riscv_general_type.h"
#include "instruction/riscv_ins.h"
#include "instruction/riscv_ins_type.h"

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
  int index = entries_write_.FrontIndex();
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
  int index = entries_read_.FrontIndex();
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

void ReorderBuffer::Print() {
  int index = entries_read_.FrontIndex();
  std::cout << "ReorderBuffer😉: " << std::endl;
  std::cout << "ins\tstate\n";
  while (index != INVALID_ENTRY) {
    auto ins = entries_read_[index].GetIns();
    std::cout << ToString(ins.GetInsType()) << "\t" << ToString(entries_read_[index].GetState()) << "\n";
    entries_read_.Next(index);
  }
}

}  // namespace riscv