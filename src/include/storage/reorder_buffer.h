#pragma once

#include "common/config.h"
#include "container/circular_queue.hpp"
#include "instruction/riscv_ins.h"
#include "storage/registers.h"

namespace riscv {

class ReorderBufferEntry {
 public:
  ReorderBufferEntry();

 private:
  bool busy_;
  RiscvIns *ins_;  // used in the commit state
  u32 value_;      // the result of instruction
  TomasuloState state_;
  u32 supposed_pc_;
};

class ReorderBuffer {
 public:
  bool IsBusy(int index);
  bool IsReady(int index);

  bool IsFull();

  u32 GetValue(int index);
  void SetValue(int index, u32 value);
  void SetSupposedPc(int index, u32 value);
  TomasuloState GetState(int index);

  // TODO(celve): please init everything
  void Init(int index);
  void SetIns(int index, RiscvIns *ins);
  RiscvIns *GetIns(int index);
  void MakeBusy(int index);

  int GetFront();

  int Push();

 private:
  CircularQueue<ReorderBufferEntry> entries_;
};

}  // namespace riscv