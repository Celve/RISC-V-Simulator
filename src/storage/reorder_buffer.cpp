#include "storage/reorder_buffer.h"

#include "instruction/riscv_ins.h"

namespace riscv {

ReorderBuffer::ReorderBufferEntry::ReorderBufferEntry() {
  busy_ = false;
  ins_ = nullptr;
  state_ = TomasuloState::kUndefine;
}

void ReorderBuffer::SetIns(int index, RiscvIns *ins) {
  // TODO(celve): please at the same time set the status
}

}  // namespace riscv