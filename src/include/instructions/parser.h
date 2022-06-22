#pragma once

#include "common/config.h"
#include "common/utils.h"
#include "instructions/btype_ins.h"
#include "instructions/itype_ins.h"
#include "instructions/jtype_ins.h"
#include "instructions/riscv_ins.h"
#include "instructions/rtype_ins.h"
#include "instructions/utype_ins.h"
#include "storage/memory.h"
#include "storage/registers.h"

namespace riscv {

RISCVIns *GenerateIns(u32 ins, Memory *memory, Registers *regs);

RISCVIns *GenerateIns(u32 number1, u32 number2, u32 number3, u32 number4, Memory *memory,
                      Registers *regs);

}  // namespace riscv