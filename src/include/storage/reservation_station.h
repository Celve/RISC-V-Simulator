#pragma once

#include "instruction/riscv_ins.h"

namespace riscv {

class ReservationStationEntry {
 public:
  ReservationStationEntry();

  void SetVj(u32 value);
  void SetVk(u32 value);
  void SetQj(u32 value);
  void SetQk(u32 value);
  void SetDest(u32 value);
  void MakeBusy();

 private:
  bool busy_;
  RiscvIns *ins_;
  u32 vj_;
  u32 vk_;
  u32 qj_;
  u32 qk_;
  u32 dest_;
};

class ReservationStation {
 public:
  int Available();
  void SetVj(int index, u32 value);
  void SetVk(int index, u32 value);
  void SetQj(int index, u32 value);
  void SetQk(int index, u32 value);
  void SetDest(int index, u32 value);
  void SetIns(int index, RiscvIns *ins);
  u32 GetVj(int index);
  u32 GetVk(int index);
  u32 GetQj(int index);
  u32 GetQk(int index);
  RiscvIns *GetIns(int index);

  void MakeBusy(int index);
  void Init(int index);

  bool IsFull();
  int FindReady();

  int GetFront();
  void GetNext(int &index);

  void Pop(int index);

 private:
  ReservationStationEntry entries_[RESERVATION_STATION_SIZE];
  u32 size_;
};

}  // namespace riscv