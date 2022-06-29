#include "storage/reorder_buffer.h"

#include <cassert>
#include <ios>
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
  state_ = TomasuloState::kUndefine;
  supposed_pc_ = INVALID_ADDRESS;
}

ReorderBuffer::ReorderBuffer() { ensured_read_ = ensured_write_ = QUEUE_SIZE - 1; }

void ReorderBuffer::IncreaseEnsured(int delta) {
  ensured_write_ += delta;
  if (ensured_write_ >= QUEUE_SIZE) {
    ensured_write_ -= QUEUE_SIZE;
  }
}

int ReorderBuffer::AttemptToIncreaseEnsured() {
  int temp = ensured_read_;
  int count = 0;
  while (true) {
    entries_read_.Next(temp);
    if (temp == INVALID_ENTRY) {
      return count;
    }
    auto general_type = entries_read_[temp].GetIns().GetGeneralType();
    if (general_type == RiscvGeneralType::BType) {
      return count;
    }
    ensured_write_ = temp;
    count += int(general_type == RiscvGeneralType::LType || general_type == RiscvGeneralType::SType);
  }
}

int ReorderBuffer::Push() {
  int index = entries_write_.Expand();
  // assert(index != INVALID_ENTRY);
  // if (index != INVALID_ENTRY) {
  // Init(index);
  // }
  return index;
}

bool ReorderBuffer::Pop() {
  int index = entries_write_.FrontIndex();
  if (index != INVALID_ENTRY) {
    Init(index);
    entries_write_.PopFront();
    return true;
  }
  return false;
}

void ReorderBuffer::Update() {
  entries_read_ = entries_write_;
  ensured_read_ = ensured_write_;
}

void ReorderBuffer::Reset() {
  entries_write_.Clear();
  ensured_write_ = QUEUE_SIZE - 1;
}

void ReorderBuffer::Print() {
  int index = entries_read_.FrontIndex();
  std::cout << "ReorderBuffer😉: " << std::endl;
  std::cout << std::dec << ensured_read_ << std::endl;
  std::cout << "pc\tins\tid\tstate\tvalue\tdest\n";
  while (index != INVALID_ENTRY) {
    auto ins = entries_read_[index].GetIns();
    std::cout << std::hex << entries_read_[index].GetPc() << "\t" << std::dec << index << "\t"
              << ToString(ins.GetInsType()) << "\t" << ToString(entries_read_[index].GetState()) << "\t"
              << entries_read_[index].GetValue() << "\t" << entries_read_[index].GetIns().GetRd() << "\n";
    entries_read_.Next(index);
  }
}

}  // namespace riscv