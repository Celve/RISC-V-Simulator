#pragma once

#include "prediction/branch_predictor.h"
#include "storage/common_data_bus.h"
#include "storage/instruction_queue.h"
#include "storage/load_store_buffer.h"
#include "storage/memory.h"
#include "storage/registers.h"
#include "storage/reorder_buffer.h"
#include "storage/reservation_station.h"
#include "unit/arithmetic_logic_unit.h"
#include "unit/memory_cell.h"

namespace riscv {

class Tomasulo {
  using RS = ReservationStation;

 public:
  explicit Tomasulo(Registers *regs, Memory *memory, InstructionQueue *iq, ReorderBuffer *rob, ReservationStation *rss,
                    LoadStoreBuffer *lsb, CommonDataBus *cdb, BranchPredictor *bp, ArithmeticLogicUnit *general_calc,
                    ArithmeticLogicUnit *address_calc, MemoryCell *mc);
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
  void SendToMemoryCell(int lsb_index);
  bool CalculateAddress();

  bool WriteResult();

  template <class Buffer>
  void TraverseToSet(u32 dest, u32 value, Buffer *buffer);

  bool Commit();
  void Reset();

  void Update();

 private:
  Registers *regs_;
  Memory *memory_;
  InstructionQueue *iq_;
  ReorderBuffer *rob_;
  ReservationStation *rss_;
  LoadStoreBuffer *lsb_;
  CommonDataBus *cdb_;
  BranchPredictor *bp_;

  ArithmeticLogicUnit *general_calc_;
  ArithmeticLogicUnit *address_calc_;

  MemoryCell *mc_;
};

}  // namespace riscv