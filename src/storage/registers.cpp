#include "storage/registers.h"

#include <cstring>

namespace riscv {

Registers::Registers() {
  pc_ = 0;
  memset(regs_, 0, sizeof(regs_));
  memset(reorder_, 0, sizeof(reorder_));
}

u32 Registers::GetReg(int index) { return regs_[index]; }

void Registers::SetReg(int index, u32 value) {
  if (index != 0) {
    regs_[index] = value;
  }
}

u32 Registers::GetReorder(int index) { return reorder_[index]; }

void Registers::SetReorder(int index, u32 value) { reorder_[index] = value; }

u32 Registers::GetPc() { return pc_; }

void Registers::SetPc(u32 value) { pc_ = value; }

void Registers::IncreasePc(int value) { pc_ += value; }

}  // namespace riscv