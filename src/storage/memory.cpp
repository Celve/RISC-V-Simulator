#include "storage/memory.h"

#include <cstring>

namespace riscv {

Memory::Memory() { memset(units_, 0, sizeof(units_)); }

u32 Memory::GetByte(int index) { return units_[index]; }

u32 Memory::GetHalf(int index) { return GetByte(index) | (GetByte(index + 1) << 8); }

u32 Memory::GetWord(int index) { return GetHalf(index) | (GetHalf(index + 2) << 16); }

void Memory::SetByte(int index, u32 value) { units_[index] = value & 0xFF; }

void Memory::SetHalf(int index, u32 value) {
  SetByte(index, value);
  SetByte(index + 1, value >> 8);
}

void Memory::SetWord(int index, u32 value) {
  SetHalf(index, value);
  SetHalf(index + 2, value >> 16);
}

}  // namespace riscv