#pragma once

#include "prediction/branch_prediction.h"
#include "storage/common_data_bus.h"
#include "storage/instruction_queue.h"
#include "storage/load_store_buffer.h"
#include "storage/memory.h"
#include "storage/registers.h"
#include "storage/reorder_buffer.h"
#include "storage/reservation_station.h"
#include "unit/arithmetic_logic_unit.h"

namespace riscv {

class Tomasulo {
  using RS = ReservationStation;

 public:
  Tomasulo() = default;
  ~Tomasulo() = default;

  Registers *GetRegs() { return regs_; }
  Memory *GetMemory() { return memory_; }

  bool Fetch();

  bool Issue();
  template <class Buffer>
  void FetchRs(u32 rs, Buffer *buffer, int index);
  template <class Buffer>
  void FetchRt(u32 rt, Buffer *buffer, int index);

  bool Execute();
  bool LoadAndStore();
  bool CalculateAddress();

  bool WriteResult();

  template <class Buffer>
  void TraverseToSet(u32 dest, u32 value, Buffer *buffer);

  bool Commit();

 private:
  InstructionQueue *iq_;
  Registers *regs_;
  Memory *memory_;
  ReorderBuffer *rob_;
  ReservationStation *rss_;
  LoadStoreBuffer *lsb_;
  BranchPrediction *bp_;
  CommonDataBus *cdb_;

  ArithmeticLogicUnit *general_calc_;
  ArithmeticLogicUnit *address_calc_;
};

}  // namespace riscv