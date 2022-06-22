#include "common/config.h"
#include "common/utils.h"
#include "gtest/gtest.h"
#include "instructions/jtype_ins.h"
#include "instructions/parser.h"
#include "instructions/riscv_type_ins.h"
#include "instructions/utype_ins.h"

TEST(UtilsTest, Reorder) {
  riscv::u32 res = riscv::AdjoinFourHex(0x37, 0x17, 0x00, 0x00);
  EXPECT_EQ(riscv::Get6To0(res), 55);
  riscv::RISCVTypeIns *ins = riscv::GenerateIns(0x37, 0x17, 0x00, 0x00);
  auto *real_ins = dynamic_cast<riscv::UTypeIns *>(ins);
  ASSERT_NE(real_ins, nullptr);
  EXPECT_EQ(real_ins->GetRd(), 14);
  EXPECT_EQ(real_ins->GetImm(), 1);
  delete real_ins;
}

TEST(UtilsTest, Random) {
  riscv::RISCVTypeIns *ins = riscv::GenerateIns(0xef, 0x10, 0x00, 0x04);
  auto *real_ins = dynamic_cast<riscv::JTypeIns *>(ins);
  ASSERT_NE(real_ins, nullptr);
  EXPECT_EQ(real_ins->GetImm(), 0x1044);
  delete real_ins;
}
