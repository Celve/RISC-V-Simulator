#include "storage/tomasulo.h"

namespace riscv {

Tomasulo::Tomasulo(Registers *regs, Memory *memory, InstructionQueue *iq, ReorderBuffer *rob, ReservationStation *rss,
                   LoadStoreBuffer *lsb, CommonDataBus *cdb, BranchPredictor *bp, ArithmeticLogicUnit *general_calc,
                   ArithmeticLogicUnit *address_calc)
    : regs_(regs),
      memory_(memory),
      iq_(iq),
      rob_(rob),
      rss_(rss),
      lsb_(lsb),
      cdb_(cdb),
      bp_(bp),
      general_calc_(general_calc),
      address_calc_(address_calc) {}

/******************************************************************************
 * FETCH
 ******************************************************************************/
bool Tomasulo::Fetch() {
  if (iq_->IsStalled() && iq_->GetQ() != INVALID_ENTRY) {
    return false;
  }
  if (iq_->IsFull()) {
    return false;
  }

  auto pc = regs_->GetPc();
  auto hexs = memory_->GetWord(pc);
  if (hexs == 0xFF00513) {
    return false;
  }
  auto ins = RiscvIns(hexs);
  auto supposed_pc = regs_->GetPc() + 4;  // completed immediately

  /* the instruction jalr would stall the fetching process */
  if (ins.GetInsType() == RiscvInsType::JALR && !iq_->IsStalled()) {
    iq_->MakeStalled();
    iq_->SetQ(ins.GetRs());
    return false;
  }

  /* compute the destination in one cycle */
  if (ins.GetInsType() == RiscvInsType::JALR) {
    supposed_pc = (iq_->GetV() + int(ins.GetImm())) & (~1);
  } else if (ins.GetGeneralType() == RiscvGeneralType::BType) {
    if (bp_->Predict(pc)) {
      supposed_pc = regs_->GetPc() + ins.GetImm();
    }
  } else if (ins.GetGeneralType() == RiscvGeneralType::JType) {
    supposed_pc = regs_->GetPc() + ins.GetImm();
  }
  iq_->Push(hexs, pc, supposed_pc);
  regs_->SetPc(supposed_pc);
  return true;
}

/******************************************************************************
 * ISSUE
 ******************************************************************************/
bool Tomasulo::Issue() {
  if (iq_->IsEmpty()) {
    return false;
  }

  auto iq_front = iq_->Front();
  iq_->Pop();
  auto hex = iq_front.GetHex();
  auto pc = iq_front.GetPc();
  auto supposed_pc = iq_front.GetSupposedPc();

  RiscvIns ins(hex);
  if (ins.GetGeneralType() == RiscvGeneralType::UType) {
    if (rob_->IsFull()) {
      return false;
    }
    int rob_index = rob_->Push();
    rob_->Init(rob_index);
    rob_->SetIns(rob_index, ins);
    rob_->SetValue(rob_index, int(ins.GetImm()) + (ins.GetInsType() == RiscvInsType::LUI ? 0U : pc));
    rob_->SetSupposedPc(rob_index, supposed_pc);
    rob_->SetState(rob_index, TomasuloState::kIssue);
    regs_->SetReorder(ins.GetRd(), rob_index);
  } else if (ins.GetGeneralType() == RiscvGeneralType::JType) {
    // TODO(celve): I even don't need to put it into ROB?
  } else if (ins.GetGeneralType() == RiscvGeneralType::RType || ins.GetGeneralType() == RiscvGeneralType::IType ||
             ins.GetGeneralType() == RiscvGeneralType::BType) {
    /* find avaiable RS and ROB */
    if (rss_->IsFull() || rob_->IsFull()) {
      return false;
    }

    /* for all instructions */
    int rss_index = rss_->Available();
    int rob_index = rob_->Push();
    rss_->Init(rss_index);
    rob_->Init(rob_index);
    // TODO(celve): I haven't use the busy value
    rss_->SetA(rss_index, pc);
    rss_->MakeBusy(rss_index);
    rss_->SetDest(rss_index, rob_index);
    rob_->SetIns(rob_index, ins);
    rob_->SetSupposedPc(rob_index, supposed_pc);
    rob_->SetState(rob_index, TomasuloState::kIssue);

    if (ins.GetGeneralType() == RiscvGeneralType::BType) {
      FetchRs(ins.GetRs(), rss_, rss_index);
      FetchRt(ins.GetRt(), rss_, rss_index);
    } else if (ins.GetGeneralType() == RiscvGeneralType::IType) {
      FetchRs(ins.GetRs(), rss_, rss_index);
      rss_->SetVk(rss_index, ins.GetImm());
      regs_->SetReorder(ins.GetRd(), rob_index);
    } else if (ins.GetGeneralType() == RiscvGeneralType::RType) {
      FetchRs(ins.GetRs(), rss_, rss_index);
      FetchRt(ins.GetRt(), rss_, rss_index);
      regs_->SetReorder(ins.GetRd(), rob_index);
    }
  } else {
    int lsb_index = lsb_->Push();
    int rob_index = rob_->Push();
    lsb_->Init(lsb_index);
    rob_->Init(rob_index);
    FetchRs(ins.GetRs(), lsb_, lsb_index);
    // TODO(celve): I haven't use the busy value
    lsb_->MakeBusy(lsb_index);
    lsb_->SetDest(lsb_index, rob_index);
    rob_->SetIns(rob_index, ins);
    rob_->SetSupposedPc(rob_index, supposed_pc);
    rob_->SetState(rob_index, TomasuloState::kIssue);
    /* for store */
    if (ins.GetGeneralType() == RiscvGeneralType::SType) {
      FetchRs(ins.GetRs(), lsb_, lsb_index);
      FetchRt(ins.GetRt(), lsb_, lsb_index);
      lsb_->SetA(lsb_index, ins.GetImm());
    }

    /* for load */
    if (ins.GetGeneralType() == RiscvGeneralType::LType) {
      FetchRs(ins.GetRs(), lsb_, lsb_index);
      lsb_->SetA(lsb_index, ins.GetImm());
      regs_->SetReorder(ins.GetRd(), rob_index);
    }

    /* update ready count */
    if (rob_->GetBranchCount() == 0U) {
      lsb_->IncreaseReadyCount(1);
    }
  }
  return true;
}

template <class Buffer>
void Tomasulo::FetchRs(u32 rs, Buffer *buffer, int index) {
  if (rs == INVALID_REGISTER) {
    return;
  }
  if (regs_->IsBusy(rs)) {
    auto h = regs_->GetReorder(rs);
    if (rob_->IsReady(h)) {
      buffer->SetVj(index, rob_->GetValue(h));
      buffer->SetQj(index, 0);
    } else {
      buffer->SetQj(index, h);
    }
  } else {
    buffer->SetVj(index, regs_->GetReg(rs));
  }
}

template <class Buffer>
void Tomasulo::FetchRt(u32 rt, Buffer *buffer, int index) {
  if (rt == INVALID_REGISTER) {
    return;
  }
  if (regs_->IsBusy(rt)) {
    auto h = regs_->GetReorder(rt);
    if (rob_->IsReady(h)) {
      buffer->SetVk(index, rob_->GetValue(h));
      buffer->SetQk(index, 0);
    } else {
      buffer->SetQk(index, h);
    }
  } else {
    buffer->SetVk(index, regs_->GetReg(rt));
  }
}

/******************************************************************************
 * Execute
 ******************************************************************************/
bool Tomasulo::Execute() {
  int rss_index = rss_->FindReady();
  if (rss_index == INVALID_ENTRY) {
    return false;
  }
  auto ins = rss_->GetIns(rss_index);
  auto rob_index = rss_->GetDest(rss_index);
  cdb_->Push(rob_index, general_calc_->Execute(ins.GetInsType(), rss_->GetVj(rss_index), rss_->GetVk(rss_index),
                                               rss_->GetA(rss_index), ins.GetImm()));
  rob_->SetState(rob_index, TomasuloState::kExecute);
  rss_->Pop(rss_index);

  return true;
}

bool Tomasulo::LoadAndStore() {
  if (lsb_->IsEmpty()) {
    return false;
  }
  int lsb_index = lsb_->GetFront();
  if (!lsb_->IsReady(lsb_index)) {
    return false;
  }

  auto ins = lsb_->GetIns(lsb_index);
  if (ins.GetGeneralType() == RiscvGeneralType::LType) {
    lsb_->IncreaseCount(lsb_index);
    if (lsb_->IsCompleted(lsb_index)) {
      auto result = lsb_->GetVk(lsb_index);
      auto rob_index = lsb_->GetDest(lsb_index);
      cdb_->Push(rob_index, result);
      rob_->SetState(rob_index, TomasuloState::kExecute);
      lsb_->Pop();
    }
  } else {
    lsb_->IncreaseCount(lsb_index);
    if (lsb_->IsCompleted(lsb_index)) {
      lsb_->Pop();
    }
  }
  return true;
}

bool Tomasulo::CalculateAddress() {
  if (lsb_->IsEmpty()) {
    return false;
  }
  int lsb_index = lsb_->GetFront();
  while (lsb_index != INVALID_ENTRY) {
    if (lsb_->GetQj(lsb_index) == INVALID_ENTRY) {
      auto ins = lsb_->GetIns(lsb_index);
      auto address = address_calc_->Execute(ins.GetInsType(), lsb_->GetA(lsb_index), lsb_->GetVj(lsb_index));
      lsb_->SetA(lsb_index, address);
      return true;
    }
    lsb_->GetNext(lsb_index);
  }
  return false;
}

/******************************************************************************
 * Write Result
 ******************************************************************************/
bool Tomasulo::WriteResult() {
  if (cdb_->IsEmpty()) {
    return false;
  }
  auto cdb_front = cdb_->Front();
  u32 dest = cdb_front.GetDest();
  u32 value = cdb_front.GetValue();
  cdb_->Pop();

  /* for instruction queue */
  if (iq_->GetQ() == dest) {
    iq_->SetQ(INVALID_ENTRY);
    iq_->SetV(value);
  }

  /* for load and store buffer */
  TraverseToSet(dest, value, lsb_);
  /* for reorder buffer */
  rob_->SetValue(dest, value);
  rob_->SetState(dest, TomasuloState::kWriteResult);
  /* for reservation stations */
  TraverseToSet(dest, value, rss_);

  return true;
}

template <class Buffer>
void Tomasulo::TraverseToSet(u32 dest, u32 value, Buffer *buffer) {
  auto index = buffer->GetFront();
  while (index != INVALID_ENTRY) {
    if (buffer->GetQj(index) == dest) {
      buffer->SetQj(index, INVALID_ENTRY);
      buffer->SetVj(index, value);
    }
    if (buffer->GetQk(index) == dest) {
      buffer->SetQk(index, INVALID_ENTRY);
      buffer->SetVk(index, value);
    }
    buffer->GetNext(index);
  }
}

/******************************************************************************
 * Commit
 ******************************************************************************/
bool Tomasulo::Commit() {
  int rob_index = rob_->GetFront();
  if (rob_index == INVALID_ENTRY || rob_->GetState(rob_index) != TomasuloState::kWriteResult) {
    return false;
  }
  u32 dest = rob_->GetIns(rob_index).GetRd();
  u32 value = rob_->GetValue(rob_index);
  if (dest != INVALID_REGISTER) {
    regs_->SetReg(dest, value);
  }
  regs_->SetReorder(dest, INVALID_REORDER);
  rob_->SetState(rob_index, TomasuloState::kCommit);

  auto ins = rob_->GetIns(rob_index);
  if (ins.GetGeneralType() != RiscvGeneralType::BType) {
    rob_->Pop();
    return true;
  }
  auto correct_pc = rob_->GetValue(rob_index);
  if (correct_pc != rob_->GetSupposedPc(rob_index)) {
    // the speculation is wrong, therefore reset
    regs_->SetPc(correct_pc);
    Reset();
    auto hexs_pc = rob_->GetPc(rob_index);
    bp_->Feedback(hexs_pc, correct_pc != hexs_pc + 4);
  } else {
    int count = rob_->GetRelativeCount();
    lsb_->IncreaseReadyCount(count);
  }
  rob_->Pop();
  // TODO(celve): add judgement for appending load and store buffer
  return true;
}

void Tomasulo::Reset() {
  lsb_->Reset();
  iq_->Reset();
  rob_->Reset();
  rss_->Reset();
  cdb_->Reset();
}

/******************************************************************************
 * Update
 ******************************************************************************/
void Tomasulo::Update() {
  rob_->Update();
  rss_->Update();
  lsb_->Update();
  iq_->Update();
  cdb_->Update();
}

}  // namespace riscv