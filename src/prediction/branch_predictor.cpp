#include "prediction/branch_predictor.h"

#include <cstring>

namespace riscv {

BranchPredictor::BranchPredictor() {
  memset(counter_, 0, sizeof(counter_));
  memset(history_, 0, sizeof(history_));
}

bool BranchPredictor::Predict(u32 addr) { return (counter_[addr + history_[addr]] & 2) != 0; }

void BranchPredictor::Feedback(u32 addr, bool is_taken) {
  auto real_addr = addr + history_[addr];
  if (is_taken) {
    counter_[real_addr] = (counter_[real_addr] == 3 ? 3 : counter_[real_addr] + 1);
  } else {
    counter_[real_addr] = (counter_[real_addr] == 0 ? 0 : counter_[real_addr] - 1);
  }
  history_[addr] = (history_[addr] << 1) | int(is_taken);
  history_[addr] &= 3;
}

}  // namespace riscv