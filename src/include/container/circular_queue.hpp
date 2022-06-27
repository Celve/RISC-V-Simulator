#pragma once

#include "common/config.h"

namespace riscv {

template <class T>
class CircularQueue {
 public:
  bool Full() const { return size_ == QUEUE_SIZE; }
  bool Empty() const { return size_ == 0; }

  void Push(const T &value) {
    if (Full()) {
      return;
    }
    queue_[Increase(tail_)] = value;
    ++size_;
  }

  int Expand() {
    if (Full()) {
      return INVALID_ENTRY;
    }
    return Increase(tail_);
  }

  void Next(int &index) {
    if (index == tail_) {
      index = INVALID_ENTRY;
    } else {
      if (++index >= QUEUE_SIZE) {
        index = 0;
      }
    }
  }

  int Rank(int index) {
    if (index >= head_) {
      return index - head_;
    }
    return QUEUE_SIZE - head_ + index;
  }

  void PopFront() {
    if (Empty()) {
      return;
    }
    Increase(head_);
    --size_;
  }

  void PopBack() {
    if (Empty()) {
      return;
    }
    Decrease(tail_);
    --size_;
  }

  int Front() { return head_; }

  u32 Size() { return size_; }

  T &operator[](int index) { return queue_[index]; }

 private:
  u32 Increase(u32 &iter) {
    if (++iter >= QUEUE_SIZE) {
      return iter = 0;
    }
    return iter;
  }

  void Decrease(u32 &iter) {
    if (--iter < 0) {
      iter = QUEUE_SIZE - 1;
    }
  }

  u32 head_;
  u32 tail_;
  u32 size_;
  T queue_[QUEUE_SIZE];
};

}  // namespace riscv