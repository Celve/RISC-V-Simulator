#pragma once

#include "common/config.h"
#include "common/utils.h"
#include "instructions/b_ins.h"
#include "instructions/i_ins.h"
#include "instructions/j_ins.h"
#include "instructions/riscv_ins.h"
#include "instructions/r_ins.h"
#include "instructions/u_ins.h"
#include "storage/memory.h"
#include "storage/registers.h"

namespace riscv {

RiscvIns *GenerateIns(u32 ins, Memory *memory, Registers *regs);

RiscvIns *GenerateIns(u32 number1, u32 number2, u32 number3, u32 number4, Memory *memory,
                      Registers *regs);

}  // namespace riscv