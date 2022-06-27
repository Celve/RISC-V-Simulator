#include "storage/registers.h"

#include <cstdio>
#include <cstring>
#include <string>

namespace riscv {

Register::Register() {
  reg_ = 0;
  reorder_ = INVALID_ENTRY;
}

u32 Register::GetValue() { return reg_; }

void Register::SetValue(u32 value) { reg_ = value; }

u32 Register::GetReorder() { return reorder_; }

void Register::SetReorder(u32 value) { reorder_ = value; }

bool Register::IsBusy() { return reorder_ != INVALID_REORDER; }

u32 Registers::GetReg(int index) { return regs_read_[index].GetValue(); }

void Registers::SetReg(int index, u32 value) {
  if (index != 0) {
    regs_write_[index].SetValue(value);
  }
}

u32 Registers::GetReorder(int index) { return regs_read_[index].GetReorder(); }

void Registers::SetReorder(int index, u32 value) { regs_write_[index].SetReorder(value); }

u32 Registers::GetPc() { return pc_read_.GetValue(); }

void Registers::SetPc(u32 value) { pc_write_.SetValue(value); }

/**
 * @brief
 * the value is relative to the in pc, increase twice make the first invalid
 * @param value
 */
void Registers::IncreasePc(int value) { pc_write_.SetValue(pc_read_.GetValue() + value); }

bool Registers::IsBusy(int index) { return regs_read_[index].IsBusy(); }

void Registers::Update() {
  memcpy(regs_read_, regs_write_, sizeof(regs_read_));
  pc_read_ = pc_write_;
}

void Registers::Print() {
  std::string reg_names[] = {"0",  "ra", "sp", "gp", "tp",  "t0",  "t1", "t2", "s0", "s1", "a0",
                             "a1", "a2", "a3", "a4", "a5",  "a6",  "a7", "s2", "s3", "s4", "s5",
                             "s6", "s7", "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"};
  auto print_row = [&](int l, int r) {
    for (int i = l; i < r; ++i) {
      printf("%s\t", reg_names[i].c_str());
    }
    printf("\n");
    for (int i = l; i < r; ++i) {
      if (GetReorder(i) != INVALID_ENTRY) {
        printf("➡️%u\t", GetReorder(i));
      } else {
        printf("%u\t", GetReg(i));
      }
    }
    printf("\n");
  };
  printf("Registers\n");
  print_row(0, 8);
  print_row(8, 16);
  print_row(16, 24);
  print_row(24, 32);
}

}  // namespace riscv