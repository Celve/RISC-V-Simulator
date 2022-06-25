#include "storage/tomasulo.h"

#include "instruction/riscv_general_type.h"
#include "instruction/riscv_ins.h"
#include "storage/reservation_station.h"

namespace riscv {

Tomasulo::Tomasulo() {
  regs_ = new Registers;
  memory_ = new Memory;
}

Tomasulo::~Tomasulo() {
  delete regs_;
  delete memory_;
}

/******************************************************************************
 * FETCH
 ******************************************************************************/
bool Tomasulo::Fetch() {
  if (iq_->IsFull()) {
    return false;
  }
  // TODO(celve): find a way to return
  // TODO(celve): add branch prediction here, which costs none, for simplicity
  auto pc = regs_->GetPc();
  auto hexs = memory_->GetWord(pc);
  iq_->Push(hexs);
  regs_->IncreasePc(4);
  return true;
}

/******************************************************************************
 * ISSUE
 ******************************************************************************/
bool Tomasulo::Issue() {
  if (iq_->IsEmpty()) {
    return false;
  }
  auto hexs = iq_->Front();
  iq_->Pop();
  RiscvIns *ins = new RiscvIns(hexs);

  if (ins->GetGeneralType() != RiscvGeneralType::LType && ins->GetGeneralType() != RiscvGeneralType::SType) {
    /* find avaiable RS and ROB */
    int rss_index = rss_->Available();
    int rob_index = rob_->Available();
    if (rss_index == INVALID_ENTRY || rss_index == INVALID_ENTRY) {
      return false;
    }

    /* for all instructions */
    rss_->Init(rss_index);
    rob_->Init(rob_index);
    FetchRs(ins->GetRs(), rss_index);
    rss_->MakeBusy(rss_index);
    rss_->SetDest(rss_index, rob_index);
    rob_->SetIns(rob_index, ins);

    /* for FP operations and store */
    if (ins->GetGeneralType() == RiscvGeneralType::BType) {
      FetchRt(ins->GetRt(), rss_index);
    } else if (ins->GetGeneralType() == RiscvGeneralType::IType) {
      regs_->SetReorder(ins->GetRd(), rob_index);
    } else if (ins->GetGeneralType() == RiscvGeneralType::JType) {
      // TODO(celve): consider whether to do computation inside alu
    } else if (ins->GetGeneralType() == RiscvGeneralType::RType) {
      FetchRt(ins->GetRt(), rss_index);
      regs_->SetReorder(ins->GetRd(), rob_index);
    } else if (ins->GetGeneralType() == RiscvGeneralType::UType) {
      // TODO(celve): consider whether to do computation inside alu
    }
  } else {
    int lsb_index = lsb_->Available();
    int rob_index = rob_->Available();
    lsb_->Init(lsb_index);
    rob_->Init(rob_index);
    FetchRs(ins->GetRs(), lsb_index);
    lsb_->MakeBusy(lsb_index);
    lsb_->SetDest(lsb_index, rob_index);
    rob_->SetIns(rob_index, ins);

    /* for store */
    if (ins->GetGeneralType() == RiscvGeneralType::SType) {
      FetchRt(ins->GetRt(), lsb_index);
      lsb_->SetA(lsb_index, ins->GetImm());
    }

    /* for load */
    if (ins->GetGeneralType() == RiscvGeneralType::LType) {
      lsb_->SetA(lsb_index, ins->GetImm());
      regs_->SetReorder(ins->GetRd(), rob_index);
    }
  }
  return true;
}

void Tomasulo::FetchRs(u32 rs, int rss_index) {
  if (rs == INVALID_REGISTER) {
    return;
  }
  if (regs_->IsBusy(rs)) {
    auto h = regs_->GetReorder(rs);
    if (rob_->IsReady(h)) {
      rss_->SetVj(rss_index, rob_->GetValue(h));
      rss_->SetQj(rss_index, 0);
    } else {
      rss_->SetQj(rss_index, h);
    }
  } else {
    rss_->SetVj(rss_index, regs_->GetReg(rs));
  }
}

void Tomasulo::FetchRt(u32 rt, int rss_index) {
  if (rt == INVALID_REGISTER) {
    return;
  }
  if (regs_->IsBusy(rt)) {
    auto h = regs_->GetReorder(rt);
    if (rob_->IsReady(h)) {
      rss_->SetVk(rss_index, rob_->GetValue(h));
      rss_->SetQk(rss_index, 0);
    } else {
      rss_->SetQk(rss_index, h);
    }
  } else {
    rss_->SetVk(rss_index, regs_->GetReg(rt));
  }
}

/******************************************************************************
 * Execute
 ******************************************************************************/
void Tomasulo::Execute() {}

void Tomasulo::LoadAndStore() {}

}  // namespace riscv