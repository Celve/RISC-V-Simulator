#pragma once

#include "common/config.h"

namespace riscv {

class Memory {
 public:
  Memory();

  u32 GetByte(int index);
  u32 GetHalf(int index);
  u32 GetWord(int index);
  void SetByte(int index, u32 value);
  void SetHalf(int index, u32 value);
  void SetWord(int index, u32 value);

 private:
  u8 units_[MEMORY_SIZE];
};

}  // namespace riscv