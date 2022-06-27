#pragma once

#include "common/config.h"
namespace riscv {

class BranchPredictorUnit {
 public:
  BranchPredictorUnit();
  bool Predict();
  void Feedback(bool is_taken);

 private:
  u8 counter_;
};

class BranchPredictor {
 public:
  bool Predict(u32 addr);
  void Feedback(u32 addr, bool is_taken);

 private:
  BranchPredictorUnit bps_[MEMORY_SIZE];
};

}  // namespace riscv
