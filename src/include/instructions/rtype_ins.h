#pragma once

#include "common/config.h"
#include "instructions/riscv_type_ins.h"
#include "storage/memory.h"
#include "storage/registers.h"

namespace riscv {

/**
 * @brief
 * 10 r-type instruction
 */
class RTypeIns : public RISCVTypeIns {
 public:
  enum class RIns { ADD, SUB, SLL, SLT, SLTU, XOR, SRL, SRA, OR, AND };

  explicit RTypeIns(u32 ins, Memory *memory, Registers *regs) : memory_(memory), regs_(regs) {
    Init(ins);
  }
  void Init(u32 ins) override;
  void Execute() override;

  u32 GetRs1() { return rs1_; }
  u32 GetRs2() { return rs2_; }
  u32 GetRd() { return rd_; }

 private:
  void IdentifyOp(u32 part1, u32 part2);

  RIns ins_;
  u32 rs1_;
  u32 rs2_;
  u32 rd_;

  Memory *memory_;
  Registers *regs_;
};

}  // namespace riscv