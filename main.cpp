#include <cstdio>
#include <cstring>
#include <iostream>

#include "common/config.h"
#include "common/utils.h"
#include "instruction/riscv_ins.h"
#include "prediction/branch_predictor.h"
#include "storage/common_data_bus.h"
#include "storage/instruction_queue.h"
#include "storage/load_store_buffer.h"
#include "storage/memory.h"
#include "storage/registers.h"
#include "storage/reorder_buffer.h"
#include "storage/reservation_station.h"
#include "storage/tomasulo.h"
#include "unit/arithmetic_logic_unit.h"

char hexs[MAX_CHARS_PER_LINE];
riscv::Registers *regs;
riscv::Memory *memory;
riscv::InstructionQueue *iq;
riscv::ReorderBuffer *rob;
riscv::ReservationStation *rss;
riscv::LoadStoreBuffer *lsb;
riscv::CommonDataBus *cdb;
riscv::BranchPredictor *bp;
riscv::ArithmeticLogicUnit *general_calc;
riscv::ArithmeticLogicUnit *address_calc;

riscv::Tomasulo *tomasulo;

void SetUp() {
  regs = new riscv::Registers;
  memory = new riscv::Memory;
  iq = new riscv::InstructionQueue;
  rob = new riscv::ReorderBuffer;
  rss = new riscv::ReservationStation;
  lsb = new riscv::LoadStoreBuffer;
  cdb = new riscv::CommonDataBus;
  bp = new riscv::BranchPredictor;
  general_calc = new riscv::ArithmeticLogicUnit;
  address_calc = new riscv::ArithmeticLogicUnit;
  tomasulo = new riscv::Tomasulo(regs, memory, iq, rob, rss, lsb, cdb, bp, general_calc, address_calc);
}

void TearDown() {
  delete regs;
  delete memory;
  delete iq;
  delete rob;
  delete rss;
  delete lsb;
  delete cdb;
  delete bp;
  delete general_calc;
  delete address_calc;
  delete tomasulo;
}

void Input() {
  int hex_cursor;
  while (scanf("%s", hexs) != EOF) {
    if (hexs[0] == '@') {
      // indicate the start point of the program
      sscanf(hexs, "@%x", &hex_cursor);
    } else {
      // the body of the program
      int n = strlen(hexs);
      for (int i = 0; i < n; i += 3) {
        riscv::u32 hex;
        sscanf(hexs, "%x", &hex);
        memory->SetByte(hex_cursor++, hex);
      }
    }
  }
}

void Execute() {
  unsigned cycles = 0;
  while (true) {
    ++cycles;
    bool state = false;
    /* fetch */
    state |= tomasulo->Fetch();
    /* issue */
    state |= tomasulo->Issue();
    /* execute */
    state |= tomasulo->Execute();
    state |= tomasulo->CalculateAddress();
    state |= tomasulo->LoadAndStore();
    /* write result */
    state |= tomasulo->WriteResult();
    /* commit */
    state |= tomasulo->Commit();
    /* update */
    tomasulo->Update();
    if (!state) {
      printf("%u\n", regs->GetReg(10) & 0xFFU);
      break;
    }
  }
}

int main() {
  SetUp();
  Input();
  Execute();
  TearDown();
}