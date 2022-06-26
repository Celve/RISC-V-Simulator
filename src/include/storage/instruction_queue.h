#pragma once

#include <queue>

#include "instruction/riscv_ins.h"
#include "storage/reservation_station.h"

namespace riscv {

class InstructionQueueNode {
 public:
  InstructionQueueNode(u32 ins_hex, u32 pc, u32 supposed_pc);

  u32 GetHex();
  u32 GetPc();
  u32 GetSupposedPc();

 private:
  u32 ins_hex_;
  u32 pc_;
  u32 supposed_pc_;
};

class InstructionQueue {
 public:
  bool Push(u32 ins_hex, u32 pc, u32 supposed_pc);
  InstructionQueueNode Front();
  bool Pop();

  bool IsEmpty();
  bool IsFull();
  bool IsStalled();

  // TODO(celve): please also modify dest here
  void MakeStalled();

  void SetQ(u32 value);
  void SetV(u32 value);
  u32 GetV();
  u32 GetQ();

 private:
  std::queue<InstructionQueueNode> queue_;
  bool stalled_;
  u32 v_;
  u32 q_;
};

}  // namespace riscv