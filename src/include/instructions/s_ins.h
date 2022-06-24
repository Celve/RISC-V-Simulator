#pragma once

#include "common/config.h"
#include "instructions/riscv_ins.h"
#include "storage/memory.h"
#include "storage/registers.h"

namespace riscv {

/**
 * @brief
 * 3 s-type instrction
 */
class SIns : public RiscvIns {
 public:
  enum class SInsType { SB, SH, SW };

  explicit SIns(u32 ins, Memory *memory, Registers *regs) : memory_(memory), regs_(regs) {
    Init(ins);
  }
  void Init(u32 ins) override;
  void Execute() override;

  u32 GetImm() { return imm_; }
  u32 GetRs1() { return rs1_; }
  u32 GetRs2() { return rs2_; }

 private:
  void IdentifyOp(u32 ins);
  void CalcImm(u32 ins);

  SInsType ins_;
  u32 rs1_;
  u32 rs2_;
  u32 imm_;

  Memory *memory_;
  Registers *regs_;
};
}  // namespace riscv