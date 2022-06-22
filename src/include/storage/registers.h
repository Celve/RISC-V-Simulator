#pragma once

#include "common/config.h"

namespace riscv {

class Registers {
 public:
  Registers();

  u32 GetReg(int index);
  void SetReg(int index, u32 value);
  u32 GetReorder(int index);
  void SetReorder(int index, u32 value);
  u32 GetPc();
  void SetPc(u32 value);
  void IncreasePc(int value);

 private:
  u32 pc_;
  u32 regs_[REGISTER_NUMBER];
  u32 reorder_[REGISTER_NUMBER];
};

}  // namespace riscv