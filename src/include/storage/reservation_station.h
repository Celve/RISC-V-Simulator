#pragma once

#include "instructions/riscv_ins.h"

namespace riscv {

class ReservationStation {
 public:
  bool InsertEntry(RiscvIns* ins);

 protected:
  class ReservationStationEntry {
   public:
    ReservationStationEntry();
    friend ReservationStation;

   private:
    bool busy_;
    RiscvIns* ins_;
    u32 vj_;
    u32 vk_;
    u32 qj_;
    u32 qk_;
  };

 private:
  ReservationStationEntry entries_[RESERVATION_STATION_SIZE];
};

}  // namespace riscv