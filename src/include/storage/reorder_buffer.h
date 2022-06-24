#pragma once

#include "container/circular_queue.hpp"
#include "instruction/riscv_ins.h"
#include "storage/registers.h"

namespace riscv {

class ReorderBuffer {
 public:
  enum class TomasuloState { kUndefine, kIssue, kExecute, kWriteResult, kCommit };

  bool IsBusy(int index);
  bool IsReady(int index);

  int Available();

  u32 GetValue(int index);

  // TODO(celve): please init everything
  void Init(int index);
  void SetIns(int index, RiscvIns *ins);
  void MakeBusy(int index);

 protected:
  class ReorderBufferEntry {
   public:
    ReorderBufferEntry();
    friend ReorderBuffer;

   private:
    bool busy_;
    RiscvIns *ins_;  // used in the commit state
    u32 value_;      // the result of instruction
    TomasuloState state_;
  };

 private:
  CircularQueue<ReorderBufferEntry> entries_[REORDER_BUFFER_SIZE];
};

}  // namespace riscv