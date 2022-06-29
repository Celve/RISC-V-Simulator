#pragma once

#include <cassert>
#include <iostream>

#include "common/config.h"

namespace riscv {

template <class T>
class CircularQueue {
 public:
  CircularQueue() {
    head_ = 0;
    tail_ = QUEUE_SIZE - 1;
    size_ = 0;
  }

  bool Full() const { return size_ == QUEUE_SIZE; }
  bool Empty() const { return size_ == 0; }

  void Clear() {
    head_ = 0;
    tail_ = QUEUE_SIZE - 1;
    size_ = 0;
  }

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
    ++size_;
    if (tail_ >= QUEUE_SIZE) {
      std::cerr << tail_ << std::endl;
      assert(false);
    }
    return Increase(tail_);
  }

  void Next(int &index) {
    assert(index < QUEUE_SIZE);
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
    if (tail_ >= QUEUE_SIZE) {
      std::cerr << tail_ << std::endl;
      assert(false);
    }
  }

  void PopBack() {
    if (Empty()) {
      return;
    }
    Decrease(tail_);
    --size_;
    if (tail_ >= QUEUE_SIZE) {
      std::cerr << tail_ << std::endl;
      assert(false);
    }
  }

  int FrontIndex() { return size_ == 0 ? INVALID_ENTRY : head_; }

  T &Front() { return queue_[head_]; }

  u32 Size() { return size_; }

  T &operator[](int index) {
    assert(index < QUEUE_SIZE);
    return queue_[index];
  }

  u32 GetHead() { return head_; }

  u32 GetTail() { return tail_; }

 private:
  u32 Increase(u32 &iter) {
    if (iter == QUEUE_SIZE - 1) {
      return iter = 0;
    }
    return ++iter;
  }

  void Decrease(u32 &iter) {
    if (iter == 0) {
      iter = QUEUE_SIZE - 1;
    } else {
      --iter;
    }
    if (iter >= QUEUE_SIZE) {
      std::cerr << iter << std::endl;
      assert(false);
    }
  }

  u32 head_;
  u32 tail_;
  u32 size_;
  T queue_[QUEUE_SIZE];
};

}  // namespace riscv