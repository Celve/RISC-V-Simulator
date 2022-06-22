#include "instructions/rtype_ins.h"

#include "common/config.h"
#include "common/utils.h"
#include "storage/registers.h"

namespace riscv {

void RTypeIns::Init(u32 ins) {
  u32 part1 = Get31To25(ins);
  rs2_ = Get24To20(ins);
  rs1_ = Get19To15(ins);
  u32 part2 = Get14To12(ins);
  rd_ = Get11To7(ins);

  IdentifyOp(part1, part2);
}

void RTypeIns::IdentifyOp(u32 part1, u32 part2) {
  if (part1 == 0 && part2 == 0) {
    ins_ = RIns::ADD;
  } else if (part1 == 32 && part2 == 0) {
    ins_ = RIns::SUB;
  } else if (part1 == 0 && part2 == 1) {
    ins_ = RIns::SLL;
  } else if (part1 == 0 && part2 == 2) {
    ins_ = RIns::SLT;
  } else if (part1 == 0 && part2 == 3) {
    ins_ = RIns::SLTU;
  } else if (part1 == 0 && part2 == 4) {
    ins_ = RIns::XOR;
  } else if (part1 == 0 && part2 == 5) {
    ins_ = RIns::SRL;
  } else if (part1 == 32 && part2 == 5) {
    ins_ = RIns::SRA;
  } else if (part1 == 0 && part2 == 6) {
    ins_ = RIns::OR;
  } else if (part1 == 0 && part2 == 7) {
    ins_ = RIns::AND;
  } else {
    // TODO(celve): resolve a error to be put in here
  }
}

void RTypeIns::Execute() {
  u32 reg1 = regs_->GetReg(rs1_);
  u32 reg2 = regs_->GetReg(rs2_);
  switch (ins_) {
    case RIns::ADD:
      regs_->SetReg(rd_, reg1 + reg2);
      break;
    case RIns::SUB:
      regs_->SetReg(rd_, reg2 - reg1);
      break;
    case RIns::SLL:
      regs_->SetReg(rd_, reg1 << reg2);
      break;
    case RIns::SLT:
      // TODO(celve): I'm not sure here
      regs_->SetReg(rd_, static_cast<u32>(static_cast<int>(reg1) < static_cast<int>(reg2)));
      break;
    case RIns::SLTU:
      regs_->SetReg(rd_, static_cast<u32>(reg1 < reg2));
      break;
    case RIns::XOR:
      regs_->SetReg(rd_, reg1 ^ reg2);
      break;
    case RIns::SRL:
      regs_->SetReg(rd_, reg1 >> reg2);
      break;
    case RIns::SRA:
      regs_->SetReg(rd_, static_cast<int>(reg1) >> reg2);
      break;
    case RIns::OR:
      regs_->SetReg(rd_, reg1 | reg2);
      break;
    case RIns::AND:
      regs_->SetReg(rd_, reg1 & reg2);
      break;
  }
}

}  // namespace riscv