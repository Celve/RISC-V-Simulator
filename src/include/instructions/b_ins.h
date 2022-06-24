#pragma once

#include "common/config.h"
#include "instructions/riscv_ins.h"
#include "storage/memory.h"
#include "storage/registers.h"

namespace riscv {

class BIns : public RiscvIns {
 public:
  enum class BInsType { BEQ, BNE, BLT, BGE, BLTU, BGEU };

  explicit BIns(u32 ins, Memory *memory, Registers *regs) : memory_(memory), regs_(regs) {
    Init(ins);
  }
  void Init(u32 ins) override;
  void Execute() override;

  u32 GetRs1() { return rs1_; }
  u32 GetRs2() { return rs2_; }
  u32 GetImm() { return imm_; }

 private:
  void IdentifyOp(u32 part1);
  void CalcImm(u32 ins);

  BInsType ins_;
  u32 rs1_;
  u32 rs2_;
  u32 imm_;

  Memory *memory_;
  Registers *regs_;
};

}  // namespace riscv