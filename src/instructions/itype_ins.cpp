#include "instructions/itype_ins.h"

#include "common/utils.h"

namespace riscv {

void ITypeIns::Init(u32 ins) {
  u32 part1 = Get31To25(ins);
  u32 shamt = Get24To20(ins);
  imm_ = Get31To20(ins);
  rs1_ = Get19To15(ins);
  u32 part2 = Get14To12(ins);
  rd_ = Get11To7(ins);
  u32 part3 = Get6To0(ins);

  IdentifyOp(part1, part2, part3, shamt);
}

void ITypeIns::IdentifyOp(u32 part1, u32 part2, u32 part3, u32 shamt) {
  if (part2 == 0 && part3 == 103) {
    ins_ = IIns::JALR;
  } else if (part2 == 0 && part3 == 19) {
    ins_ = IIns::ADDI;
  } else if (part2 == 2 && part3 == 19) {
    ins_ = IIns::SLTI;
  } else if (part2 == 3 && part3 == 19) {
    ins_ = IIns::SLTIU;
  } else if (part2 == 4 && part3 == 19) {
    ins_ = IIns::XORI;
  } else if (part2 == 6 && part3 == 19) {
    ins_ = IIns::ORI;
  } else if (part2 == 7 && part3 == 19) {
    ins_ = IIns::ANDI;
  } else if (part1 == 0 && part2 == 1 && part3 == 19) {
    ins_ = IIns::SLLI;
    imm_ = shamt;
  } else if (part1 == 0 && part2 == 5 && part3 == 19) {
    ins_ = IIns::SRLI;
    imm_ = shamt;
  } else if (part1 == 32 && part2 == 5 && part3 == 19) {
    ins_ = IIns::SRAI;
    imm_ = shamt;
  } else {
    // TODO(celve): the error
  }
}

void ITypeIns::Execute() {
  u32 reg1 = regs_->GetReg(rs1_);
  int imm = int(imm_);
  switch (ins_) {
    case IIns::JALR:
      break;
    case IIns::ADDI:
      regs_->SetReg(rd_, reg1 + imm);
      break;
    case IIns::SLTI:
      regs_->SetReg(rd_, u32(int(reg1) < imm));
      break;
    case IIns::SLTIU:
      regs_->SetReg(rd_, u32(reg1 < u32(imm)));
      break;
    case IIns::XORI:
      regs_->SetReg(rd_, reg1 ^ imm);
      break;
    case IIns::ORI:
      regs_->SetReg(rd_, reg1 | imm);
      break;
    case IIns::ANDI:
      regs_->SetReg(rd_, reg1 & imm);
      break;
    case IIns::SLLI:
      // TODO(celve): make sure imm[5] = 0
      regs_->SetReg(rd_, reg1 << imm);
      break;
    case IIns::SRLI:
      // TODO(celve): make sure imm[5] = 0
      regs_->SetReg(rd_, reg1 >> imm);
      break;
    case IIns::SRAI:
      regs_->SetReg(rd_, int(reg1) >> imm);
      break;
  }
}

}  // namespace riscv
