#pragma once

#include "common/config.h"
namespace riscv {

class BranchPredictionUnit {
 public:
  bool Predict();

 private:
  u8 counter_;
};

class BranchPrediction {
 public:
  bool Predict(u32 addr);
  void Feedback(u32 addr, bool feedback);

 private:
  BranchPredictionUnit bps_[MEMORY_SIZE];
};

}  // namespace riscv
