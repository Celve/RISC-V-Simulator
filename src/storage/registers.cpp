#include "storage/registers.h"

#include <cstring>

namespace riscv {

Register::Register() {
  reg_ = 0;
  reorder_ = 0;
}

u32 Register::GetValue() { return reg_; }

void Register::SetValue(u32 value) { reg_ = value; }

u32 Register::GetReorder() { return reorder_; }

void Register::SetReorder(u32 value) { reorder_ = value; }

bool Register::IsBusy() { return reorder_ != INVALID_REORDER; }

u32 Registers::GetReg(int index) { return regs_org_[index].GetValue(); }

void Registers::SetReg(int index, u32 value) {
  if (index != 0) {
    regs_upd_[index].SetValue(value);
  }
}

u32 Registers::GetReorder(int index) { return regs_org_[index].GetReorder(); }

void Registers::SetReorder(int index, u32 value) { regs_upd_[index].SetReorder(value); }

u32 Registers::GetPc() { return pc_org_.GetValue(); }

void Registers::SetPc(u32 value) { pc_upd_.SetValue(value); }

/**
 * @brief
 * the value is relative to the in pc, increase twice make the first invalid
 * @param value
 */
void Registers::IncreasePc(int value) { pc_upd_.SetValue(pc_org_.GetValue() + value); }

bool Registers::IsBusy(int index) { return regs_org_[index].IsBusy(); }

void Registers::Next() {
  memcpy(regs_org_, regs_upd_, sizeof(regs_org_));
  pc_org_ = pc_upd_;
}

}  // namespace riscv