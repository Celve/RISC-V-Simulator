#pragma once

namespace riscv {

enum class RiscvInsType {
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

}  // namespace riscv