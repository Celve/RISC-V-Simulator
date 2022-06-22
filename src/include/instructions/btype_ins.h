#pragma once

#include "common/config.h"
#include "instructions/riscv_type_ins.h"

namespace riscv {

class BTypeIns : public RISCVTypeIns {
 public:
  enum class BIns { BEQ, BNE, BLT, BGE, BLTU, BGEU };

  explicit BTypeIns(u32 ins) { Init(ins); }
  void Init(u32 ins) override;
  void Execute() override;

  u32 GetRs1() { return rs1_; }
  u32 GetRs2() { return rs2_; }
  u32 GetImm() { return imm_; }

 private:
  void IdentifyOp(u32 part1);
  void CalcImm(u32 ins);

  BIns ins_;
  u32 rs1_;
  u32 rs2_;
  u32 imm_;
};

}  // namespace riscv