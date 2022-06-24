#include "common/config.h"
#include "common/utils.h"
#include "instructions/b_ins.h"
#include "instructions/i_ins.h"
#include "instructions/j_ins.h"
#include "instructions/riscv_ins.h"
#include "instructions/r_ins.h"
#include "instructions/s_ins.h"
#include "instructions/u_ins.h"
#include "storage/memory.h"
#include "storage/registers.h"

namespace riscv {

RiscvIns *GenerateIns(u32 ins, Memory *memory, Registers *regs) {
  u32 part1 = Get6To0(ins);
  if (part1 == 55 || part1 == 23) {
    // UIns(ins, memory, regs).Execute();
    return new UIns(ins, memory, regs);
  }
  if (part1 == 111) {
    // JIns(ins, memory, regs).Execute();
    return new JIns(ins, memory, regs);
  }
  if (part1 == 103 || part1 == 19 || part1 == 3) {
    // IIns(ins, memory, regs).Execute();
    return new IIns(ins, memory, regs);
  }
  if (part1 == 99) {
    // BIns(ins, memory, regs).Execute();
    return new BIns(ins, memory, regs);
  }
  if (part1 == 51) {
    // RIns(ins, memory, regs).Execute();
    return new RIns(ins, memory, regs);
  }
  if (part1 == 35) {
    // SIns(ins, memory, regs).Execute();
    return new SIns(ins, memory, regs);
  }
  /* it should not be here */
  return nullptr;
}

RiscvIns *GenerateIns(u32 number1, u32 number2, u32 number3, u32 number4, Memory *memory,
                      Registers *regs) {
  return GenerateIns(AdjoinFourHex(number1, number2, number3, number4), memory, regs);
}

}  // namespace riscv