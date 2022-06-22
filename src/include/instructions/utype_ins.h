#pragma once

#include "common/config.h"
#include "instructions/riscv_type_ins.h"

namespace riscv {

class UTypeIns : public RISCVTypeIns {
 public:
  enum class UIns { LUI, AUIPC };

  explicit UTypeIns(u32 ins) { Init(ins); }

  void Init(u32 ins) override;
  void Execute() override;

  u32 GetImm() { return imm_; }
  u32 GetRd() { return rd_; }

 private:
  void IdentifyOp(u32 part1);

  UIns ins_;
  u32 imm_;
  u32 rd_;
};

}  // namespace riscv