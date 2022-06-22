#include "common/config.h"
#include "common/utils.h"
#include "instructions/btype_ins.h"
#include "instructions/itype_ins.h"
#include "instructions/jtype_ins.h"
#include "instructions/riscv_ins.h"
#include "instructions/rtype_ins.h"
#include "instructions/stype_ins.h"
#include "instructions/utype_ins.h"
#include "storage/memory.h"
#include "storage/registers.h"

namespace riscv {

RISCVIns *GenerateIns(u32 ins, Memory *memory, Registers *regs) {
  u32 part1 = Get6To0(ins);
  if (part1 == 55 || part1 == 23) {
    return new UTypeIns(ins, memory, regs);
  }
  if (part1 == 111) {
    return new JTypeIns(ins, memory, regs);
  }
  if (part1 == 103 || part1 == 19 || part1 == 3) {
    return new ITypeIns(ins, memory, regs);
  }
  if (part1 == 99) {
    return new BTypeIns(ins, memory, regs);
  }
  if (part1 == 51) {
    return new RTypeIns(ins, memory, regs);
  }
  if (part1 == 35) {
    return new STypeIns(ins, memory, regs);
  }
  /* it should not be here */
  return nullptr;
}

RISCVIns *GenerateIns(u32 number1, u32 number2, u32 number3, u32 number4, Memory *memory,
                      Registers *regs) {
  return GenerateIns(AdjoinFourHex(number1, number2, number3, number4), memory, regs);
}

}  // namespace riscv