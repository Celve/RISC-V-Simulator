#include "storage/registers.h"

namespace riscv {

u32 Registers::GetReg(int index) { return regs_[index]; }

void Registers::SetReg(int index, u32 value) { regs_[index] = value; }

u32 Registers::GetReorder(int index) { return reorder_[index]; }

void Registers::SetReorder(int index, u32 value) { reorder_[index] = value; }

u32 Registers::GetPc() { return pc_; }

void Registers::SetPc(u32 value) { pc_ = value; }

}  // namespace riscv