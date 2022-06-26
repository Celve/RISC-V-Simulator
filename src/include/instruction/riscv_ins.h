#pragma once

#include "common/config.h"
#include "instruction/riscv_general_type.h"
#include "instruction/riscv_ins_type.h"

namespace riscv {

class RiscvIns {
 public:
  explicit RiscvIns(u32 ins);
  ~RiscvIns() = default;

  void Init(u32 ins);

  void BTypeInit(u32 ins);
  void ITypeInit(u32 ins);
  void JTypeInit(u32 ins);
  void LTypeInit(u32 ins);
  void RTypeInit(u32 ins);
  void STypeInit(u32 ins);
  void UTypeInit(u32 ins);

  u32 GetRs();
  u32 GetRt();
  u32 GetRd();
  u32 GetImm();

  RiscvGeneralType GetGeneralType();
  RiscvInsType GetInsType();

 private:
  RiscvGeneralType general_;
  RiscvInsType ins_;
  u32 rs_;
  u32 rt_;
  u32 rd_;
  u32 imm_;
};

}  // namespace riscv