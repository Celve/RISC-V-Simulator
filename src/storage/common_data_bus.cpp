#pragma once

#include "storage/common_data_bus.h"

namespace riscv {

bool CommonDataBus::Push(u32 dest, u32 value) {
  if (queue_write_.size() < COMMON_DATA_BUS_SIZE) {
    queue_write_.push(CommonDataBusNode(dest, value));
    return true;
  }
  return false;
}

bool CommonDataBus::Pop() {
  if (!queue_read_.empty()) {
    queue_read_.pop();
    queue_write_.pop();
    return true;
  }
  return false;
}

CommonDataBusNode CommonDataBus::Front() { return queue_read_.front(); }

bool CommonDataBus::IsEmpty() { return queue_read_.empty(); }

void CommonDataBus::Update() { queue_read_ = queue_write_; }

void CommonDataBus::Reset() {
  while (!queue_write_.empty()) {
    queue_write_.pop();
  }
}

}  // namespace riscv