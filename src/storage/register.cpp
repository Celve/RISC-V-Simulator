#include "storage/register.h"

namespace riscv {

Register::Register() {
  reg_ = 0;
  reorder_ = 0;
}

u32 Register::GetReg() { return reg_; }

void Register::SetReg(u32 value) { reg_ = value; }

u32 Register::GetReorder() { return reorder_; }

void Register::SetReorder(u32 value) { reorder_ = value; }

bool Register::IsBusy() { return reorder_ != INVALID_REORDER; }

}  // namespace riscv