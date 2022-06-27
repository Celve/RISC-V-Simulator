#include "instruction/riscv_ins_type.h"

namespace riscv {

std::string ToString(const RiscvInsType& riscv_ins_type) {
  switch (riscv_ins_type) {
    case RiscvInsType::BEQ:
      return "BEQ";
    case RiscvInsType::BNE:
      return "BNE";
    case RiscvInsType::BLT:
      return "BLT";
    case RiscvInsType::BGE:
      return "BGE";
    case RiscvInsType::BLTU:
      return "BLTU";
    case RiscvInsType::BGEU:
      return "BGEU";
    case RiscvInsType::JALR:
      return "JALR";
    case RiscvInsType::ADDI:
      return "ADDI";
    case RiscvInsType::SLTI:
      return "SLTI";
    case RiscvInsType::SLTIU:
      return "SLTIU";
    case RiscvInsType::XORI:
      return "XORI";
    case RiscvInsType::ORI:
      return "ORI";
    case RiscvInsType::ANDI:
      return "ANDI";
    case RiscvInsType::SLLI:
      return "SLLI";
    case RiscvInsType::SRLI:
      return "SRLI";
    case RiscvInsType::SRAI:
      return "SRAI";
    case RiscvInsType::JAL:
      return "JAL";
    case RiscvInsType::LB:
      return "LB";
    case RiscvInsType::LH:
      return "LH";
    case RiscvInsType::LW:
      return "LW";
    case RiscvInsType::LBU:
      return "LBU";
    case RiscvInsType::LHU:
      return "LHU";
    case RiscvInsType::ADD:
      return "ADD";
    case RiscvInsType::SUB:
      return "SUB";
    case RiscvInsType::SLL:
      return "SLL";
    case RiscvInsType::SLT:
      return "SLT";
    case RiscvInsType::SLTU:
      return "SLTU";
    case RiscvInsType::XOR:
      return "XOR";
    case RiscvInsType::SRL:
      return "SRL";
    case RiscvInsType::SRA:
      return "SRA";
    case RiscvInsType::OR:
      return "OR";
    case RiscvInsType::AND:
      return "AND";
    case RiscvInsType::SB:
      return "SB";
    case RiscvInsType::SH:
      return "SH";
    case RiscvInsType::SW:
      return "SW";
    case RiscvInsType::LUI:
      return "LUI";
    case RiscvInsType::AUIPC:
      return "AUIPC";
    default:
      return "Unknown";
  }
}

}  // namespace riscv