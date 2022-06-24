#pragma once

#include "common/config.h"

namespace riscv {

template <class T>
class CircularQueue {
 private:
  u32 Append(u32 &iter) {
    if (++iter >= QUEUE_SIZE) {
      iter = 0;
    }
    return iter;
  }

 public:
  bool IsFull() const { return size_ == QUEUE_SIZE; }
  bool IsEmpty() const { return size_ == 0; }

  void Push(const T &value) {
    if (IsFull()) {
      return;
    }
    queue_[Append(tail_)] = value;
    ++size_;
  }

  void Pop() {
    if (IsEmpty()) {
      return;
    }
    Append(head_);
    --size_;
  }

  T &Front() { return queue_[head_]; }

 private:
  u32 head_;
  u32 tail_;
  u32 size_;
  T queue_[QUEUE_SIZE];
};

}  // namespace riscv