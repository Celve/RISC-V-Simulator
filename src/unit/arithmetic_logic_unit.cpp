#include "unit/arithmetic_logic_unit.h"

#include "common/config.h"
#include "instruction/riscv_ins_type.h"

namespace riscv {

u32 ALU::Execute(RiscvInsType type, u32 lhs, u32 rhs) {
  switch (type) {
    case RiscvInsType::BEQ:
      return u32(int(lhs) == int(rhs));
    case RiscvInsType::BNE:
      return u32(int(lhs) != int(rhs));
    case RiscvInsType::BLT:
      return u32(int(lhs) < int(rhs));
    case RiscvInsType::BGE:
      return u32(int(lhs) >= int(rhs));
    case RiscvInsType::BLTU:
      return u32(lhs < rhs);
    case RiscvInsType::BGEU:
      return u32(lhs >= rhs);
    // case RiscvInsType::JALR:
    // return (lhs + rhs) & (~1);
    case RiscvInsType::ADDI:
      return lhs + rhs;
    case RiscvInsType::SLTI:
      return u32(int(lhs) < rhs);
    case RiscvInsType::SLTIU:
      return u32(lhs < u32(rhs));
    case RiscvInsType::XORI:
      return lhs ^ rhs;
      break;
    case RiscvInsType::ORI:
      return lhs | rhs;
      break;
    case RiscvInsType::ANDI:
      return lhs & rhs;
      break;
    case RiscvInsType::SLLI:
      return ((rhs >> 5 & 1) == 0) ? (lhs << rhs) : lhs;
    case RiscvInsType::SRLI:
      return ((rhs >> 5 & 1) == 0) ? (lhs >> rhs) : lhs;
    case RiscvInsType::SRAI:
      return ((rhs >> 5 & 1) == 0) ? (int(lhs) >> rhs) : lhs;
    // case RiscvInsType::JAL:
    // return 0U;
    case RiscvInsType::ADD:
      return lhs + rhs;
    case RiscvInsType::SUB:
      return lhs - rhs;
    case RiscvInsType::SLL:
      return lhs << (rhs & 0x1F);
    case RiscvInsType::SLT:
      // TODO(celve): I'm not sure here
      return u32(int(lhs) < int(rhs));
    case RiscvInsType::SLTU:
      return u32(lhs < rhs);
    case RiscvInsType::XOR:
      return lhs ^ rhs;
    case RiscvInsType::SRL:
      return lhs >> (rhs & 0x1F);
    case RiscvInsType::SRA:
      return (int(lhs)) >> (rhs & 0x1F);
    case RiscvInsType::OR:
      return lhs | rhs;
    case RiscvInsType::AND:
      return lhs & rhs;
    default:
      return 0U;
  }
}

}  // namespace riscv