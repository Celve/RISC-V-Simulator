#include "storage/reorder_buffer.h"

namespace riscv {

ReorderBuffer::ReorderBufferEntry::ReorderBufferEntry() {
  busy_ = false;
  ins_ = nullptr;
  state_ = TomasuloState::kUndefine;
}

bool ReorderBuffer::InsertEntry(RiscvIns *ins) {
  for (auto &entry : entries_) {
    if (!entry.busy_) {
      entry.busy_ = true;
      entry.ins_ = ins;
      entry.state_ = TomasuloState::kIssue;
      return true;
    }
  }
  return false;
}

}  // namespace riscv