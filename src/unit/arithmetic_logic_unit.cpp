#include "unit/arithmetic_logic_unit.h"

#include "common/config.h"
#include "instruction/riscv_ins_type.h"

namespace riscv {

u32 ArithmeticLogicUnit::Execute(const RiscvInsType &type, u32 lhs, u32 rhs, u32 pc, u32 imm) {
  switch (type) {
    case RiscvInsType::BEQ:
      return int(lhs) == int(rhs) ? pc + int(imm) : pc + 4;
    case RiscvInsType::BNE:
      return int(lhs) != int(rhs) ? pc + int(imm) : pc + 4;
    case RiscvInsType::BLT:
      return int(lhs) < int(rhs) ? pc + int(imm) : pc + 4;
    case RiscvInsType::BGE:
      return int(lhs) >= int(rhs) ? pc + int(imm) : pc + 4;
    case RiscvInsType::BLTU:
      return lhs < rhs ? pc + int(imm) : pc + 4;
    case RiscvInsType::BGEU:
      return lhs >= rhs ? pc + int(imm) : pc + 4;
    // case RiscvInsType::JALR:
    // return (lhs + rhs) & (~1);
    case RiscvInsType::ADDI:
      return lhs + rhs;
    case RiscvInsType::SLTI:
      return u32(int(lhs) < rhs);
    case RiscvInsType::SLTIU:
      return u32(lhs < rhs);
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
    case RiscvInsType::SB:
    case RiscvInsType::SH:
    case RiscvInsType::SW:
      return lhs + rhs;
    case RiscvInsType::LB:
    case RiscvInsType::LBU:
    case RiscvInsType::LH:
    case RiscvInsType::LHU:
    case RiscvInsType::LW:
      return lhs + rhs;
    case RiscvInsType::LUI:
    case RiscvInsType::AUIPC:
      return lhs + rhs;
    case RiscvInsType::JALR:
    case RiscvInsType::JAL:
      return lhs + rhs;
    default:
      return 0U;
  }
}

}  // namespace riscv