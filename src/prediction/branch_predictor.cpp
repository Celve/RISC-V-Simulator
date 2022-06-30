#include "prediction/branch_predictor.h"

namespace riscv {

BranchPredictor::BranchPredictor() {
  for (int i = 0; i < MEMORY_SIZE; i++) {
    counter_[i] = 0;
    history_[i] = 0;
  }
}

bool BranchPredictor::Predict(u32 addr) { return (counter_[addr + history_[addr]] & 2) != 0; }

void BranchPredictor::Feedback(u32 addr, bool is_taken) {
  counter_[addr + history_[addr]] = (counter_[addr + history_[addr]] << 1) | int(is_taken);
  counter_[addr + history_[addr]] = (counter_[addr + history_[addr]] << 1);
}

}  // namespace riscv