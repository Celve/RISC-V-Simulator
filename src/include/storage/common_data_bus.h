#pragma once

#include <queue>

#include "common/config.h"

namespace riscv {

class CommonDataBusNode {
 public:
  CommonDataBusNode(u32 dest, u32 value) : dest_(dest), value_(value) {}

  u32 GetDest() const { return dest_; }
  u32 GetValue() const { return value_; }

 private:
  u32 dest_;
  u32 value_;
};

class CommonDataBus {
 public:
  bool Push(u32 dest, u32 value);
  bool Pop();
  CommonDataBusNode Front();

  bool IsEmpty();

  void Update();
  void Reset();

 private:
  std::queue<CommonDataBusNode> queue_read_;
  std::queue<CommonDataBusNode> queue_write_;
};

}  // namespace riscv