#pragma once

#include <unordered_map>

#include "common/config.h"
namespace riscv {

class BranchPredictor {
 public:
  BranchPredictor();

  u32 GetSize() { return mapping_.size(); }

  bool Predict(u32 addr);
  void Feedback(u32 addr, bool is_taken);

 private:
  u32 Get(u32 addr);

  std::unordered_map<u32, u32> mapping_;
  int count_;
  u8 counter_[BRANCH_PREDICTOR_SIZE][256];
  u8 history_[BRANCH_PREDICTOR_SIZE];
};

}  // namespace riscv
