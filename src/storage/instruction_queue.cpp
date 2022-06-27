#include "storage/instruction_queue.h"

namespace riscv {

bool InstructionQueue::Push(u32 ins_hex, u32 pc, u32 supposed_pc) {
  if (queue_write_.size() < INSTRUCTION_QUEUE_SIZE) {
    queue_write_.push(InstructionQueueNode(ins_hex, pc, supposed_pc));
    return true;
  }
  return false;
}

InstructionQueueNode InstructionQueue::Front() { return queue_write_.front(); }

bool InstructionQueue::Pop() {
  if (!queue_read_.empty()) {
    queue_read_.pop();
    queue_write_.pop();
    return true;
  }
  return false;
}

bool InstructionQueue::IsEmpty() { return queue_read_.empty(); }

bool InstructionQueue::IsFull() { return queue_read_.size() >= INSTRUCTION_QUEUE_SIZE; }

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
  while (!queue_write_.empty()) {
    queue_write_.pop();
  }
  stalled_write_ = false;
  v_write_ = 0;
  q_write_ = 0;
}

}  // namespace riscv