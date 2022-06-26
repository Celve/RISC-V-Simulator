#pragma once

#include <queue>

#include "common/config.h"
#include "container/circular_queue.hpp"
#include "instruction/riscv_ins.h"
#include "storage/reservation_station.h"

namespace riscv {

class LoadStoreBufferEntry : public ReservationStationEntry {
 public:
  void SetA(u32 value);
  void IncreaseCount();

 private:
  u32 a_;
  u32 count_;        // the round of circle
  bool calculated_;  // whether the address has been calculated or not
};

class LoadStoreBuffer {
 public:
  void SetVj(int index, u32 value);
  void SetVk(int index, u32 value);
  void SetQj(int index, u32 value);
  void SetQk(int index, u32 value);
  void SetDest(int index, u32 value);
  void SetA(int index, u32 value);
  u32 GetVj(int index);
  u32 GetVk(int index);
  u32 GetQj(int index);
  u32 GetQk(int index);
  u32 GetDest(int index);
  u32 GetA(int index);
  RiscvIns *GetIns(int index);

  void MakeBusy(int index);
  void Init(int index);

  int Push();
  void Pop();

  int GetFront();
  void IncreaseCount(int index);
  void GetNext(int &index);

  bool IsEmpty();
  bool IsReady(int index);      // stands for its readiness for store or load in memory and the calculation of address
  bool IsCompleted(int index);  // whether it has finished 3 cycles

 private:
  CircularQueue<LoadStoreBufferEntry> entries_;
  u32 ready_size_;
};

}  // namespace riscv