#include "prediction/branch_predictor.h"

#include <cstring>

namespace riscv {

BranchPredictor::BranchPredictor() {
  memset(counter_, 0, sizeof(counter_));
  memset(history_, 0, sizeof(history_));
}

u32 BranchPredictor::Get(u32 addr) {
  if (mapping_.find(addr) == mapping_.end()) {
    return mapping_[addr] = count_++;
  }
  return mapping_[addr];
}

bool BranchPredictor::Predict(u32 addr) {
  auto curr = Get(addr);
  return (counter_[curr][history_[curr]] & 2) != 0;
}

void BranchPredictor::Feedback(u32 addr, bool is_taken) {
  auto curr = Get(addr);
  if (is_taken) {
    counter_[curr][history_[curr]] = (counter_[curr][history_[curr]] == 3 ? 3 : counter_[curr][history_[curr]] + 1);
  } else {
    counter_[curr][history_[curr]] = (counter_[curr][history_[curr]] == 0 ? 0 : counter_[curr][history_[curr]] - 1);
  }
  history_[curr] = (history_[curr] << 1) | int(is_taken);
  history_[curr] &= 0xF;
}

}  // namespace riscv