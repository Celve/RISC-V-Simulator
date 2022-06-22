#pragma once

#include "common/config.h"

namespace riscv {

class Memory {
 public:
  u32 Get(int index);
  void Set(int index, u32 value);

 private:
  u32 units_[MEMORY_SIZE];
};

}  // namespace riscv