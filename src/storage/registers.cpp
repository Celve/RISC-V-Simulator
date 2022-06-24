#include "storage/registers.h"

#include <cstring>

namespace riscv {

u32 Registers::GetReg(int index) { return regs_org_[index].GetReg(); }

void Registers::SetReg(int index, u32 value) {
  if (index != 0) {
    regs_upd_[index].SetReg(value);
  }
}

u32 Registers::GetReorder(int index) { return regs_org_[index].GetReorder(); }

void Registers::SetReorder(int index, u32 value) { regs_upd_[index].SetReorder(value); }

u32 Registers::GetPc() { return pc_org_.GetReg(); }

void Registers::SetPc(u32 value) { pc_upd_.SetReg(value); }

/**
 * @brief
 * the value is relative to the in pc, increase twice make the first invalid
 * @param value
 */
void Registers::IncreasePc(int value) { pc_upd_.SetReg(pc_org_.GetReg() + value); }

void Registers::Next() {
  memcpy(regs_org_, regs_upd_, sizeof(regs_org_));
  pc_org_ = pc_upd_;
}

}  // namespace riscv