#include "prediction/branch_predictor.h"

namespace riscv {

BranchPredictorUnit::BranchPredictorUnit() { counter_ = 0; }

bool BranchPredictorUnit::Predict() { return (counter_ & 0x2) != 0; }

void BranchPredictorUnit::Feedback(bool is_taken) {
  if (is_taken && counter_ != 0b11) {
    ++counter_;
  }
  if (!is_taken && counter_ != 0b00) {
    --counter_;
  }
}

bool BranchPredictor::Predict(u32 addr) { return bps_[addr].Predict(); }

void BranchPredictor::Feedback(u32 addr, bool is_taken) { bps_[addr].Feedback(is_taken); }

}  // namespace riscv