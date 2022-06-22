#include "instructions/rtype_ins.h"

#include "common/config.h"
#include "common/utils.h"

namespace riscv {

void RTypeIns::Init(u32 ins) {
  u32 part1 = Get31To25(ins);
  rs2_ = Get24To20(ins);
  rs1_ = Get19To15(ins);
  u32 part2 = Get14To12(ins);
  rd_ = Get11To7(ins);

  IdentifyOp(part1, part2);
}

void RTypeIns::IdentifyOp(u32 part1, u32 part2) {
  if (part1 == 0 && part2 == 0) {
    ins_ = RIns::ADD;
  } else if (part1 == 32 && part2 == 0) {
    ins_ = RIns::SUB;
  } else if (part1 == 0 && part2 == 1) {
    ins_ = RIns::SLL;
  } else if (part1 == 0 && part2 == 2) {
    ins_ = RIns::SLT;
  } else if (part1 == 0 && part2 == 3) {
    ins_ = RIns::SLTU;
  } else if (part1 == 0 && part2 == 4) {
    ins_ = RIns::XOR;
  } else if (part1 == 0 && part2 == 5) {
    ins_ = RIns::SRL;
  } else if (part1 == 32 && part2 == 5) {
    ins_ = RIns::SRA;
  } else if (part1 == 0 && part2 == 6) {
    ins_ = RIns::OR;
  } else if (part1 == 0 && part2 == 7) {
    ins_ = RIns::AND;
  } else {
    // TODO(celve): resolve a error to be put in here
  }
}

void RTypeIns::Execute() {
  switch (ins_) {
    case RIns::ADD:
      break;
    case RIns::SUB:
      break;
    case RIns::SLL:
      break;
    case RIns::SLT:
      break;
    case RIns::SLTU:
      break;
    case RIns::XOR:
      break;
    case RIns::SRL:
      break;
    case RIns::SRA:
      break;
    case RIns::OR:
      break;
    case RIns::AND:
      break;
  }
}

}  // namespace riscv