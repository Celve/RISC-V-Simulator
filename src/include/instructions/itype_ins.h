#pragma once

#include "common/config.h"
#include "common/utils.h"
#include "instructions/riscv_type_ins.h"

namespace riscv {

class ITypeIns : public RISCVTypeIns {
 public:
  enum class IIns { JALR, ADDI, SLTI, SLTIU, XORI, ORI, ANDI, SLLI, SRLI, SRAI };

  explicit ITypeIns(u32 ins) { Init(ins); }
  void Init(u32 ins) override;
  void Execute() override;

  u32 GetRs1() { return rs1_; }
  u32 GetImm() { return imm_; }
  u32 GetRd() { return rd_; }

 private:
  void IdentifyOp(u32 part1, u32 part2, u32 part3, u32 shamt);

  IIns ins_;
  u32 rs1_;
  u32 imm_;
  u32 rd_;
};

}  // namespace riscv