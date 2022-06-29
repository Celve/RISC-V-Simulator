#pragma once

#include "common/config.h"
#include "container/circular_queue.hpp"
#include "instruction/riscv_ins.h"
#include "storage/registers.h"
#include "tomasulo/tomasulo_state.h"

namespace riscv {

class ReorderBufferEntry {
 public:
  ReorderBufferEntry();

  void Init();

  void SetIns(const RiscvIns &ins) { ins_ = ins; }
  void SetValue(u32 value) { value_ = value; }
  void SetState(TomasuloState state) { state_ = state; }
  void SetSupposedPc(u32 value) { supposed_pc_ = value; }
  void SetPc(u32 value) { pc_ = value; }

  TomasuloState GetState() { return state_; }
  u32 GetValue() { return value_; }
  u32 GetSupposedPc() { return supposed_pc_; }
  u32 GetPc() { return pc_; }
  RiscvIns GetIns() { return ins_; }

 private:
  RiscvIns ins_;  // used in the commit state
  u32 value_;     // the result of instruction
  TomasuloState state_;
  u32 supposed_pc_;
  u32 pc_;
};

class ReorderBuffer {
 public:
  ReorderBuffer();

  bool IsReady(int index) { return entries_read_[index].GetState() >= TomasuloState::kWriteResult; }

  bool IsFull() { return entries_read_.Full(); }
  bool IsEmpty() { return entries_read_.Empty(); }

  u32 GetValue(int index) { return entries_read_[index].GetValue(); }
  u32 GetSupposedPc(int index) { return entries_read_[index].GetSupposedPc(); }
  u32 GetPc(int index) { return entries_read_[index].GetPc(); }
  TomasuloState GetState(int index) { return entries_read_[index].GetState(); }
  RiscvIns GetIns(int index) { return entries_write_[index].GetIns(); }

  void SetValue(int index, u32 value) { entries_write_[index].SetValue(value); }
  void SetSupposedPc(int index, u32 value) { entries_write_[index].SetSupposedPc(value); }
  void SetPc(int index, u32 value) { entries_write_[index].SetPc(value); }
  void SetIns(int index, const RiscvIns &ins) { entries_write_[index].SetIns(ins); }
  void SetState(int index, TomasuloState state) { entries_write_[index].SetState(state); }

  int AttemptToIncreaseEnsured();
  void IncreaseEnsured(int delta);

  void Init(int index) { entries_write_[index].Init(); }

  int GetFront() { return entries_read_.FrontIndex(); }
  int Push();
  bool Pop();

  void Update();
  void Reset();

  void Print();

 private:
  CircularQueue<ReorderBufferEntry> entries_read_;
  CircularQueue<ReorderBufferEntry> entries_write_;
  u32 ensured_read_;
  u32 ensured_write_;
};

}  // namespace riscv