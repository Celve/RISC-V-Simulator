#pragma once

#include <queue>

#include "instruction/riscv_ins.h"

namespace riscv {

class InstructionQueue {
 public:
  bool Push(u32);
  u32 Front();
  bool Pop();

  bool IsEmpty();
  bool IsFull();

 private:
  std::queue<u32> queue_;
};

}  // namespace riscv