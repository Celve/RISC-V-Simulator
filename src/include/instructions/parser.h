#pragma once

#include "common/config.h"
#include "common/utils.h"
#include "instructions/btype_ins.h"
#include "instructions/itype_ins.h"
#include "instructions/jtype_ins.h"
#include "instructions/riscv_type_ins.h"
#include "instructions/rtype_ins.h"
#include "instructions/utype_ins.h"

namespace riscv {

RISCVTypeIns *GenerateIns(u32 ins);

RISCVTypeIns *GenerateIns(u32 number1, u32 number2, u32 number3, u32 number4);

}  // namespace riscv