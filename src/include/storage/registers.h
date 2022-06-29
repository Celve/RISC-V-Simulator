#pragma once

#include "common/config.h"

namespace riscv {

class Register {
 public:
  Register();

  u32 GetValue();
  void SetValue(u32 value);
  u32 GetReorder();
  void SetReorder(u32 value);

  bool IsBusy();

  void Reset();

 private:
  u32 reg_;
  u32 reorder_;
};

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

  bool IsBusy(int index);

  void Update();
  void Reset();

  void Print();

 private:
  Register pc_read_;
  Register pc_write_;
  Register regs_read_[REGISTER_NUMBER];
  Register regs_write_[REGISTER_NUMBER];
};

}  // namespace riscv