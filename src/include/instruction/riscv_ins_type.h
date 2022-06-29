#pragma once

#include <string>
namespace riscv {

enum class RiscvInsType {
  Unknown,
  BEQ,
  BNE,
  BLT,
  BGE,
  BLTU,
  BGEU,
  JALR,
  ADDI,
  SLTI,
  SLTIU,
  XORI,
  ORI,
  ANDI,
  SLLI,
  SRLI,
  SRAI,
  JAL,
  LB,
  LH,
  LW,
  LBU,
  LHU,
  ADD,
  SUB,
  SLL,
  SLT,
  SLTU,
  XOR,
  SRL,
  SRA,
  OR,
  AND,
  SB,
  SH,
  SW,
  LUI,
  AUIPC
};

std::string ToString(const RiscvInsType& riscv_ins_type);

}  // namespace riscv
