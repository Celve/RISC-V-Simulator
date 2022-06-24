#pragma once

#include "common/config.h"

namespace riscv {

class Register {
 public:
  Register();

  u32 GetReg();
  void SetReg(u32 value);
  u32 GetReorder();
  void SetReorder(u32 value);

  bool IsBusy();

 private:
  u32 reg_;
  u32 reorder_;
};

}  // namespace riscv