#pragma once

#include "instructions/riscv_ins.h"
#include "storage/register.h"

namespace riscv {

class ReorderBuffer {
 public:
  enum class TomasuloState { kUndefine, kIssue, kExecute, kWriteResult, kCommit };

  bool InsertEntry(RiscvIns *ins);

 protected:
  class ReorderBufferEntry {
   public:
    ReorderBufferEntry();
    friend ReorderBuffer;

   private:
    bool busy_;
    RiscvIns *ins_;
    TomasuloState state_;
  };

 private:
  ReorderBufferEntry entries_[REORDER_BUFFER_SIZE];
};

}  // namespace riscv