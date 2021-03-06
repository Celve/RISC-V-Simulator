#pragma once

#include <queue>

#include "common/config.h"
#include "container/circular_queue.hpp"
#include "instruction/riscv_ins.h"
#include "storage/reservation_station.h"

namespace riscv {

class LoadStoreBufferEntry : public ReservationStationEntry {
 public:
  bool IsCalculated() { return calculated_; }
  bool IsSent() { return sent_; }

  void MakeCalculated() { calculated_ = true; }
  void MakeSent() { sent_ = true; }

  void Init();

 private:
  bool calculated_;  // whether the address has been calculated or not
  bool sent_;        // whether the address has been sent or not
};

class LoadStoreBuffer {
 public:
  LoadStoreBuffer();

  void SetVj(int index, u32 value) { entries_write_[index].SetVj(value); }
  void SetVk(int index, u32 value) { entries_write_[index].SetVk(value); }
  void SetQj(int index, u32 value) { entries_write_[index].SetQj(value); }
  void SetQk(int index, u32 value) { entries_write_[index].SetQk(value); }
  void SetDest(int index, u32 value) { entries_write_[index].SetDest(value); }
  void SetA(int index, u32 value) { entries_write_[index].SetA(value); }
  void SetIns(int index, const RiscvIns &ins) { entries_write_[index].SetIns(ins); }
  void MakeBusy(int index) { entries_write_[index].MakeBusy(); }
  void MakeCalculated(int index) { entries_write_[index].MakeCalculated(); }
  void MakeSent(int index) { entries_write_[index].MakeSent(); }
  void IncreaseReadyCount(int delta) { ready_count_write_ += delta; }

  u32 GetVj(int index) { return entries_read_[index].GetVj(); }
  u32 GetVk(int index) { return entries_read_[index].GetVk(); }
  u32 GetQj(int index) { return entries_read_[index].GetQj(); }
  u32 GetQk(int index) { return entries_read_[index].GetQk(); }
  u32 GetDest(int index) { return entries_read_[index].GetDest(); }
  u32 GetA(int index) { return entries_read_[index].GetA(); }
  const RiscvIns &GetIns(int index) { return entries_read_[index].GetIns(); }
  LoadStoreBufferEntry &GetEntry(int index) { return entries_write_[index]; }

  void Init(int index) { entries_write_[index].Init(); }

  int Push();
  bool Pop();

  int GetFront() { return entries_read_.FrontIndex(); }
  // void IncreaseCount(int index) { entries_write_[index].IncreaseCount(1); }
  void GetNext(int &index) { entries_read_.Next(index); }

  bool IsEmpty() { return entries_read_.Empty(); }
  bool IsFull() { return entries_read_.Full(); }
  bool IsReady(int index);  // stands for its readiness for store or load in memory and the calculation of address
  bool IsCalculated(int index) { return entries_read_[index].IsCalculated(); }
  bool IsSent(int index) { return entries_read_[index].IsSent(); }

  void Update();
  void Reset();

  void Print();

 private:
  CircularQueue<LoadStoreBufferEntry> entries_read_;
  CircularQueue<LoadStoreBufferEntry> entries_write_;
  u32 ready_count_read_;
  u32 ready_count_write_;
};

}  // namespace riscv