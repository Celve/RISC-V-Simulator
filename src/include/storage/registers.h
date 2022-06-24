#pragma once

#include "common/config.h"
#include "storage/register.h"

namespace riscv {

class Registers {
 public:
  Registers() = default;

  u32 GetReg(int index);
  void SetReg(int index, u32 value);
  u32 GetReorder(int index);
  void SetReorder(int index, u32 value);
  u32 GetPc();
  void SetPc(u32 value);
  void IncreasePc(int value);

  void Next();

 private:
  Register pc_org_;
  Register pc_upd_;
  Register regs_org_[REGISTER_NUMBER];
  Register regs_upd_[REGISTER_NUMBER];
};

}  // namespace riscv