#pragma once

#include "common/config.h"
namespace riscv {

class BranchPredictor {
 public:
  BranchPredictor();

  bool Predict(u32 addr);
  void Feedback(u32 addr, bool is_taken);

 private:
  u8 counter_[MEMORY_SIZE];
  u8 history_[MEMORY_SIZE];
};

}  // namespace riscv
