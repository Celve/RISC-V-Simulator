#include "instructions/r_ins.h"

#include "common/config.h"
#include "common/utils.h"
#include "storage/registers.h"

namespace riscv {

void RIns::Init(u32 ins) {
  u32 part1 = Get31To25(ins);
  rs2_ = Get24To20(ins);
  rs1_ = Get19To15(ins);
  u32 part2 = Get14To12(ins);
  rd_ = Get11To7(ins);

  IdentifyOp(part1, part2);
}

void RIns::IdentifyOp(u32 part1, u32 part2) {
  if (part1 == 0 && part2 == 0) {
    ins_ = RInsType::ADD;
  } else if (part1 == 32 && part2 == 0) {
    ins_ = RInsType::SUB;
  } else if (part1 == 0 && part2 == 1) {
    ins_ = RInsType::SLL;
  } else if (part1 == 0 && part2 == 2) {
    ins_ = RInsType::SLT;
  } else if (part1 == 0 && part2 == 3) {
    ins_ = RInsType::SLTU;
  } else if (part1 == 0 && part2 == 4) {
    ins_ = RInsType::XOR;
  } else if (part1 == 0 && part2 == 5) {
    ins_ = RInsType::SRL;
  } else if (part1 == 32 && part2 == 5) {
    ins_ = RInsType::SRA;
  } else if (part1 == 0 && part2 == 6) {
    ins_ = RInsType::OR;
  } else if (part1 == 0 && part2 == 7) {
    ins_ = RInsType::AND;
  } else {
    // TODO(celve): resolve a error to be put in here
  }
}

void RIns::Execute() {
  u32 reg1 = regs_->GetReg(rs1_);
  u32 reg2 = regs_->GetReg(rs2_);
  switch (ins_) {
    case RInsType::ADD:
      regs_->SetReg(rd_, reg1 + reg2);
      break;
    case RInsType::SUB:
      regs_->SetReg(rd_, reg1 - reg2);
      break;
    case RInsType::SLL:
      regs_->SetReg(rd_, reg1 << (reg2 & 0x1F));
      break;
    case RInsType::SLT:
      // TODO(celve): I'm not sure here
      regs_->SetReg(rd_, u32(int(reg1) < int(reg2)));
      break;
    case RInsType::SLTU:
      regs_->SetReg(rd_, u32(reg1 < reg2));
      break;
    case RInsType::XOR:
      regs_->SetReg(rd_, reg1 ^ reg2);
      break;
    case RInsType::SRL:
      regs_->SetReg(rd_, reg1 >> (reg2 & 0x1F));
      break;
    case RInsType::SRA:
      regs_->SetReg(rd_, (int(reg1)) >> (reg2 & 0x1F));
      break;
    case RInsType::OR:
      regs_->SetReg(rd_, reg1 | reg2);
      break;
    case RInsType::AND:
      regs_->SetReg(rd_, reg1 & reg2);
      break;
  }
  regs_->IncreasePc(4);
}

}  // namespace riscv