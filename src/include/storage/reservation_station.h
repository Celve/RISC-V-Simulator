#pragma once

#include "instruction/riscv_ins.h"

namespace riscv {

class ReservationStationEntry {
 public:
  ReservationStationEntry();

  void Init();

  void SetVj(u32 value) { vj_ = value; }
  void SetVk(u32 value) { vk_ = value; }
  void SetQj(u32 value) { qj_ = value; }
  void SetQk(u32 value) { qk_ = value; }
  void SetDest(u32 value) { dest_ = value; }
  void SetA(u32 value) { a_ = value; }
  void SetIns(RiscvIns ins) { ins_ = ins; }
  void MakeBusy() { busy_ = true; }
  void MakeNoBusy() { busy_ = false; }

  u32 GetVj() const { return vj_; }
  u32 GetVk() const { return vk_; }
  u32 GetQj() const { return qj_; }
  u32 GetQk() const { return qk_; }
  u32 GetDest() const { return dest_; }
  u32 GetA() { return a_; }
  RiscvIns GetIns() const { return ins_; }
  bool IsBusy() const { return busy_; }
  bool IsReady() const { return qj_ == INVALID_ENTRY && qk_ == INVALID_ENTRY; }

 private:
  bool busy_;
  RiscvIns ins_;
  u32 vj_;
  u32 vk_;
  u32 qj_;
  u32 qk_;
  u32 a_;  // used for recording pc in reservation station, used for recording the target address in load store buffer
  u32 dest_;  // point to the reorder buffer
};

class ReservationStation {
 public:
  int Available();
  void SetVj(int index, u32 value) { entries_write_[index].SetVj(value); }
  void SetVk(int index, u32 value) { entries_write_[index].SetVk(value); }
  void SetQj(int index, u32 value) { entries_write_[index].SetQj(value); }
  void SetQk(int index, u32 value) { entries_write_[index].SetQk(value); }
  void SetDest(int index, u32 value) { entries_write_[index].SetDest(value); }
  void SetIns(int index, RiscvIns ins) { entries_write_[index].SetIns(ins); }
  void SetA(int index, u32 value) { entries_write_[index].SetA(value); }
  void MakeBusy(int index) { entries_write_[index].MakeBusy(); }

  u32 GetVj(int index) { return entries_read_[index].GetVj(); }
  u32 GetVk(int index) { return entries_read_[index].GetVk(); }
  u32 GetQj(int index) { return entries_read_[index].GetQj(); }
  u32 GetQk(int index) { return entries_read_[index].GetQk(); }
  u32 GetDest(int index) { return entries_read_[index].GetDest(); }
  u32 GetA(int index) { return entries_read_[index].GetA(); }
  RiscvIns GetIns(int index) { return entries_read_[index].GetIns(); }

  void Init(int index);

  bool IsFull() { return size_read_ == RESERVATION_STATION_SIZE; }
  int FindReady();

  int GetFront() { return 0; }
  void GetNext(int &index);

  void Pop(int index);

  void Update();
  void Reset();

  void Print();

 private:
  ReservationStationEntry entries_read_[RESERVATION_STATION_SIZE];
  ReservationStationEntry entries_write_[RESERVATION_STATION_SIZE];
  u32 size_read_;
  u32 size_write_;
};

}  // namespace riscv