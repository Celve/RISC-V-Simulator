#pragma once

#include "common/config.h"
#include "instructions/riscv_type_ins.h"

namespace riscv {

/**
 * @brief
 * 1 j-type instrction
 */
class JTypeIns : public RISCVTypeIns {
 public:
  enum class JIns { JAL };

  explicit JTypeIns(u32 ins) { Init(ins); }
  void Init(u32 ins) override;
  void Execute() override;

  u32 GetImm() { return imm_; }
  u32 GetRd() { return rd_; }

 private:
  void IdentifyOp(u32 ins);
  void CalcImm(u32 ins);

  JIns ins_;
  u32 imm_;
  u32 rd_;
};
}  // namespace riscv