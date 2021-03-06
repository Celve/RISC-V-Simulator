#pragma once

#include <queue>

#include "container/circular_queue.hpp"
#include "instruction/riscv_ins.h"
#include "storage/reservation_station.h"

namespace riscv {

class InstructionQueueNode {
 public:
  explicit InstructionQueueNode(u32 ins_hex = 0, u32 pc = 0, u32 supposed_pc = 0)
      : ins_hex_(ins_hex), pc_(pc), supposed_pc_(supposed_pc) {}

  u32 GetHex() const { return ins_hex_; }
  u32 GetPc() const { return pc_; }
  u32 GetSupposedPc() const { return supposed_pc_; }

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

  void MakeStalled();
  void MakeNoStalled();

  void SetV(u32 value) { v_write_ = value; }
  void SetQ(u32 value) { q_write_ = value; }
  u32 GetV() const { return v_read_; }
  u32 GetQ() const { return q_read_; }

  void Update();
  void Reset();

  void Print();

 private:
  CircularQueue<InstructionQueueNode> queue_read_;
  CircularQueue<InstructionQueueNode> queue_write_;
  bool stalled_read_;
  bool stalled_write_;
  u32 v_read_;
  u32 v_write_;
  u32 q_read_;
  u32 q_write_;
};

}  // namespace riscv