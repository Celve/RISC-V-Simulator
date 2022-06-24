#pragma once

#include <queue>

#include "common/config.h"
#include "container/circular_queue.hpp"
#include "storage/reservation_station.h"

namespace riscv {

class LoadStoreBufferEntry : public ReservationStationEntry {
 public:
 private:
  u32 count_;
  bool commit_;
};

class LoadStoreBuffer {
 public:
  void SetVj(int index, u32 value);
  void SetVk(int index, u32 value);
  void SetQj(int index, u32 value);
  void SetQk(int index, u32 value);
  void SetDest(int index, u32 value);
  void SetA(int index, u32 value);
  void MakeBusy(int index);
  void Init(int index);

  bool Execute();

 private:
  CircularQueue<LoadStoreBufferEntry> entries_[LOAD_STORE_BUFFER_SIZE];
};

}  // namespace riscv