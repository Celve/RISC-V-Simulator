#pragma once

#include <queue>

#include "common/config.h"

namespace riscv {

class CommonDataBusNode {
 public:
  u32 GetDest();
  u32 GetValue();

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

 private:
  std::queue<CommonDataBusNode> queue_;
};

}  // namespace riscv