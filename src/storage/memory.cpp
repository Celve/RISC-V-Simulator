#include "storage/memory.h"

namespace riscv {

u32 Memory::Get(int index) { return units_[index]; }

void Memory::Set(int index, u32 value) { units_[index] = value; }

}  // namespace riscv