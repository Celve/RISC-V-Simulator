#include "common/config.h"
#include "common/utils.h"
#include "instructions/btype_ins.h"
#include "instructions/itype_ins.h"
#include "instructions/jtype_ins.h"
#include "instructions/riscv_type_ins.h"
#include "instructions/rtype_ins.h"
#include "instructions/utype_ins.h"

namespace riscv {

RISCVTypeIns *GenerateIns(u32 ins) {
  u32 part1 = Get6To0(ins);
  if (part1 == 55 || part1 == 23) {
    return new UTypeIns(ins);
  }
  if (part1 == 111) {
    return new JTypeIns(ins);
  }
  if (part1 == 103 || part1 == 19 || part1 == 3) {
    return new ITypeIns(ins);
  }
  if (part1 == 99) {
    return new BTypeIns(ins);
  }
  if (part1 == 51) {
    return new RTypeIns(ins);
  }
  /* it should not be here */
  return nullptr;
}

RISCVTypeIns *GenerateIns(u32 number1, u32 number2, u32 number3, u32 number4) {
  return GenerateIns(AdjoinFourHex(number1, number2, number3, number4));
}

}  // namespace riscv