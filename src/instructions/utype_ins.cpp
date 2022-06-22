#include "instructions/utype_ins.h"

#include "common/utils.h"

namespace riscv {

void UTypeIns::Init(u32 ins) {
  imm_ = Get31To12(ins);
  rd_ = Get11To7(ins);
  u32 part1 = Get6To0(ins);
}

void UTypeIns::IdentifyOp(u32 part1) {
  if (part1 == 55) {
    ins_ = UIns::LUI;
  } else if (part1 == 23) {
    ins_ = UIns::AUIPC;
  } else {
    // TODO(celve): add throw
  }
}

void UTypeIns::Execute() {
  switch (ins_) {
    case UIns::LUI:
      break;
    case UIns::AUIPC:
      break;
  }
}

}  // namespace riscv