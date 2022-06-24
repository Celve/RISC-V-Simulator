#pragma once

#include "storage/instruction_queue.h"
#include "storage/load_buffer.h"
#include "storage/memory.h"
#include "storage/registers.h"
#include "storage/reorder_buffer.h"
#include "storage/reservation_station.h"

namespace riscv {

class Tomasulo {
  using RS = ReservationStation;

 public:
  Tomasulo();
  ~Tomasulo();

  Registers *GetRegs() { return regs_; }
  Memory *GetMemory() { return memory_; }

  bool Fetch();

  bool Issue();

  void Execute();
  void LoadAndStore();

  void WriteResult();

  void Commit();

  void FetchRs(u32 rs, int rss_index);
  void FetchRt(u32 rt, int rss_index);

 private:
  InstructionQueue *iq_;
  Registers *regs_;
  Memory *memory_;
  ReorderBuffer *rob_;
  ReservationStation *rss_;
  LoadBuffer *lb_;
};

}  // namespace riscv