#include "storage/instruction_queue.h"

#include <iostream>

namespace riscv {

bool InstructionQueue::Push(u32 ins_hex, u32 pc, u32 supposed_pc) {
  if (queue_write_.Size() < INSTRUCTION_QUEUE_SIZE) {
    queue_write_.Push(InstructionQueueNode(ins_hex, pc, supposed_pc));
    return true;
  }
  return false;
}

InstructionQueueNode InstructionQueue::Front() { return queue_write_.Front(); }

bool InstructionQueue::Pop() {
  if (!queue_read_.Empty()) {
    queue_read_.PopFront();
    queue_write_.PopFront();
    return true;
  }
  return false;
}

bool InstructionQueue::IsEmpty() { return queue_read_.Empty(); }

bool InstructionQueue::IsFull() { return queue_read_.Size() >= INSTRUCTION_QUEUE_SIZE; }

bool InstructionQueue::IsStalled() { return stalled_read_; }

void InstructionQueue::MakeStalled() { stalled_write_ = true; }

void InstructionQueue::MakeNoStalled() { stalled_write_ = false; }

void InstructionQueue::Update() {
  v_read_ = v_write_;
  q_read_ = q_write_;
  stalled_read_ = stalled_write_;
  queue_read_ = queue_write_;
}

void InstructionQueue::Reset() {
  while (!queue_write_.Empty()) {
    queue_write_.PopFront();
  }
  stalled_write_ = false;
  v_write_ = 0;
  q_write_ = 0;
}

void InstructionQueue::Print() {
  int index = queue_read_.FrontIndex();
  std::cout << "InstructionQueue: " << std::endl;
  std::cout << "type\trs\trt\trd\timm\n";
  while (index != INVALID_ENTRY) {
    auto hex = queue_read_[index].GetHex();
    auto ins = RiscvIns(hex);
    auto ins_type = ins.GetInsType();
    std::cout << static_cast<std::underlying_type<RiscvInsType>::type>(ins_type) << "\t"
              << (ins.GetRs() == INVALID_REGISTER ? -1 : ins.GetRs()) << "\t"
              << (ins.GetRt() == INVALID_REGISTER ? -1 : ins.GetRt()) << "\t"
              << (ins.GetRd() == INVALID_REGISTER ? -1 : ins.GetRd()) << "\t"
              << (ins.GetImm() == INVALID_IMMEDIATE ? -1 : ins.GetImm()) << "\n";
    queue_read_.Next(index);
  }
}

}  // namespace riscv