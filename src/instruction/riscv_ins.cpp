#include "instruction/riscv_ins.h"

#include "common/config.h"
#include "common/utils.h"
#include "instruction/riscv_general_type.h"
#include "instruction/riscv_ins_type.h"
#include "storage/registers.h"

namespace riscv {

RiscvIns::RiscvIns(u32 ins) {
  rs_ = INVALID_REGISTER;
  rt_ = INVALID_REGISTER;
  rd_ = INVALID_REGISTER;
  imm_ = INVALID_IMMEDIATE;
  Init(ins);
}

RiscvInsType RiscvIns::GetInsType() { return ins_; }

RiscvGeneralType RiscvIns::GetGeneralType() { return general_; }

void RiscvIns::Init(u32 ins) {
  u32 part1 = Get6To0(ins);
  if (part1 == 55 || part1 == 23) {
    UTypeInit(ins);
  } else if (part1 == 111) {
    JTypeInit(ins);
  } else if (part1 == 103 || part1 == 19) {
    ITypeInit(ins);
  } else if (part1 == 3) {
    LTypeInit(ins);
  } else if (part1 == 99) {
    BTypeInit(ins);
  } else if (part1 == 51) {
    RTypeInit(ins);
  } else if (part1 == 35) {
    STypeInit(ins);
  } else {
    assert(false);
    // TODO(celve): throw an error
  }
}

/**
 * @brief
 * B type includes rs, rt, and imm
 * it should be executed by
 */
void RiscvIns::BTypeInit(u32 ins) {
  general_ = RiscvGeneralType::BType;
  rt_ = Get24To20(ins);
  rs_ = Get19To15(ins);
  u32 part1 = Get14To12(ins);
  imm_ = Extend12(((ins >> 31 & 0x1) << 12) | ((ins >> 25 & 0x3F) << 5) | ((ins >> 8 & 0xF) << 1) |
                  ((ins >> 7 & 0x1) << 11));
  if (part1 == 0) {
    ins_ = RiscvInsType::BEQ;
  } else if (part1 == 1) {
    ins_ = RiscvInsType::BNE;
  } else if (part1 == 4) {
    ins_ = RiscvInsType::BLT;
  } else if (part1 == 5) {
    ins_ = RiscvInsType::BGE;
  } else if (part1 == 6) {
    ins_ = RiscvInsType::BLTU;
  } else if (part1 == 7) {
    ins_ = RiscvInsType::BGEU;
  } else {
    // TODO(celve): add throw here
  }
}

/**
 * @brief
 * I type includes rs, rd, and imm
 * it should be executed by alu
 */
void RiscvIns::ITypeInit(u32 ins) {
  general_ = RiscvGeneralType::IType;
  u32 part1 = Get31To25(ins);
  u32 shamt = Get24To20(ins);
  imm_ = Get31To20(ins);
  rs_ = Get19To15(ins);
  u32 part2 = Get14To12(ins);
  rd_ = Get11To7(ins);
  u32 part3 = Get6To0(ins);

  if (part2 == 0 && part3 == 103) {
    ins_ = RiscvInsType::JALR;
  } else if (part2 == 0 && part3 == 19) {
    ins_ = RiscvInsType::ADDI;
  } else if (part2 == 2 && part3 == 19) {
    ins_ = RiscvInsType::SLTI;
  } else if (part2 == 3 && part3 == 19) {
    ins_ = RiscvInsType::SLTIU;
  } else if (part2 == 4 && part3 == 19) {
    ins_ = RiscvInsType::XORI;
  } else if (part2 == 6 && part3 == 19) {
    ins_ = RiscvInsType::ORI;
  } else if (part2 == 7 && part3 == 19) {
    ins_ = RiscvInsType::ANDI;
  } else if (part1 == 0 && part2 == 1 && part3 == 19) {
    ins_ = RiscvInsType::SLLI;
    imm_ = shamt;
  } else if (part1 == 0 && part2 == 5 && part3 == 19) {
    ins_ = RiscvInsType::SRLI;
    imm_ = shamt;
  } else if (part1 == 32 && part2 == 5 && part3 == 19) {
    ins_ = RiscvInsType::SRAI;
    imm_ = shamt;
  } else {
    assert(false);
    // TODO(celve): the error
  }

  imm_ = Extend11(imm_);
}

/**
 * @brief
 * J type includes rd, imm
 * it should be stored by reservation station
 */
void RiscvIns::JTypeInit(u32 ins) {
  general_ = RiscvGeneralType::JType;
  imm_ = Extend20(((ins >> 31 & 0x1) << 20) | ((ins >> 21 & 0x3FF) << 1) | ((ins >> 20 & 0x1) << 11) |
                  ((ins >> 12 & 0xFF) << 12));
  rd_ = Get11To7(ins);
  ins_ = RiscvInsType::JAL;
}

/**
 * @brief
 * L type includes rs, rt, imm
 * it should be executed by load and store buffer
 */
void RiscvIns::LTypeInit(u32 ins) {
  general_ = RiscvGeneralType::LType;
  imm_ = Extend11(Get31To20(ins));
  rs_ = Get19To15(ins);
  u32 part1 = Get14To12(ins);
  rd_ = Get11To7(ins);

  if (part1 == 0) {
    ins_ = RiscvInsType::LB;
  } else if (part1 == 1) {
    ins_ = RiscvInsType::LH;
  } else if (part1 == 2) {
    ins_ = RiscvInsType::LW;
  } else if (part1 == 4) {
    ins_ = RiscvInsType::LBU;
  } else if (part1 == 5) {
    ins_ = RiscvInsType::LHU;
  } else {
    // TODO(celve): throw en error
  }
}

/**
 * @brief
 * R type includes rs, rt, and rd
 */
void RiscvIns::RTypeInit(u32 ins) {
  general_ = RiscvGeneralType::RType;
  u32 part1 = Get31To25(ins);
  rt_ = Get24To20(ins);
  rs_ = Get19To15(ins);
  u32 part2 = Get14To12(ins);
  rd_ = Get11To7(ins);

  if (part1 == 0 && part2 == 0) {
    ins_ = RiscvInsType::ADD;
  } else if (part1 == 32 && part2 == 0) {
    ins_ = RiscvInsType::SUB;
  } else if (part1 == 0 && part2 == 1) {
    ins_ = RiscvInsType::SLL;
  } else if (part1 == 0 && part2 == 2) {
    ins_ = RiscvInsType::SLT;
  } else if (part1 == 0 && part2 == 3) {
    ins_ = RiscvInsType::SLTU;
  } else if (part1 == 0 && part2 == 4) {
    ins_ = RiscvInsType::XOR;
  } else if (part1 == 0 && part2 == 5) {
    ins_ = RiscvInsType::SRL;
  } else if (part1 == 32 && part2 == 5) {
    ins_ = RiscvInsType::SRA;
  } else if (part1 == 0 && part2 == 6) {
    ins_ = RiscvInsType::OR;
  } else if (part1 == 0 && part2 == 7) {
    ins_ = RiscvInsType::AND;
  } else {
    // TODO(celve): resolve a error to be put in here
  }
}

/**
 * @brief
 * S type includes rs, rt, and imm
 */
void RiscvIns::STypeInit(u32 ins) {
  general_ = RiscvGeneralType::SType;
  imm_ = Extend11(((ins >> 25 & 0x7F) << 5) | (ins >> 7 & 0x1F));
  rt_ = Get24To20(ins);
  rs_ = Get19To15(ins);
  u32 part1 = Get14To12(ins);
  if (part1 == 0) {
    ins_ = RiscvInsType::SB;
  } else if (part1 == 1) {
    ins_ = RiscvInsType::SH;
  } else if (part1 == 2) {
    ins_ = RiscvInsType::SW;
  } else {
    // TODO(celve): throw an error
  }
}

/**
 * @brief
 * U type includes rd, imm
 */
void RiscvIns::UTypeInit(u32 ins) {
  general_ = RiscvGeneralType::UType;
  imm_ = Get31To12(ins) << 12;
  rd_ = Get11To7(ins);
  u32 part1 = Get6To0(ins);
  if (part1 == 55) {
    ins_ = RiscvInsType::LUI;
  } else if (part1 == 23) {
    ins_ = RiscvInsType::AUIPC;
  } else {
    // TODO(celve): add throw
  }
}

u32 RiscvIns::GetRs() { return rs_; }

u32 RiscvIns::GetRt() { return rt_; }

u32 RiscvIns::GetRd() { return rd_; }

u32 RiscvIns::GetImm() { return imm_; }

}  // namespace riscv