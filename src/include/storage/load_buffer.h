#pragma once

#include "common/config.h"
#include "storage/reservation_station.h"

namespace riscv {

class LoadBufferEntry : public ReservationStationEntry {
 public:
 private:
  u32 count_;
  bool commit_;
};

class LoadBuffer {
 public:
  int Available();
  void SetVj(int index, u32 value);
  void SetVk(int index, u32 value);
  void SetQj(int index, u32 value);
  void SetQk(int index, u32 value);
  void SetDest(int index, u32 value);
  void SetA(int index, u32 value);
  void MakeBusy(int index);
  void Init(int index);

 private:
  LoadBufferEntry *entries_[LOAD_STORE_BUFFER_SIZE];
};

}  // namespace riscv