#include "storage/load_store_buffer.h"

#include <iostream>

#include "common/config.h"
#include "storage/reservation_station.h"

namespace riscv {

void LoadStoreBufferEntry::Init() {
  ReservationStationEntry::Init();
  SetA(INVALID_ADDRESS);
  count_ = 0;
  calculated_ = false;
}

LoadStoreBuffer::LoadStoreBuffer() {
  ready_count_read_ = 0;
  ready_count_write_ = 0;
}

int LoadStoreBuffer::Push() {
  int index = entries_write_.Expand();
  if (index != INVALID_ENTRY) {
    Init(index);
  }
  return index;
}

bool LoadStoreBuffer::Pop() {
  int index = entries_write_.FrontIndex();
  // if (IsCompleted(index)) {
  // Init(index);
  entries_write_.PopFront();
  --ready_count_read_;
  --ready_count_write_;
  return true;
  // }
  return false;
}

bool LoadStoreBuffer::IsReady(int index) {
  return entries_read_[index].IsCalculated() && entries_read_.Rank(index) < ready_count_read_ &&
         GetQk(index) == INVALID_ENTRY;
}

void LoadStoreBuffer::Update() {
  entries_read_ = entries_write_;
  ready_count_read_ = ready_count_write_;
}

void LoadStoreBuffer::Reset() {
  // TODO(celve): I should use read instead of write
  while (entries_write_.Size() > ready_count_write_) {
    entries_write_.PopBack();
  }
}

void LoadStoreBuffer::Print() {
  int index = entries_read_.FrontIndex();
  std::cout << "LoadStoreBuffer😉: " << std::endl;
  std::cout << "The ready count is " << ready_count_read_ << std::endl;
  std::cout << "type\taddress\tvalue\tcount\t \n";
  while (index != INVALID_ENTRY) {
    auto ins = entries_read_[index].GetIns();
    auto ins_type = ins.GetInsType();
    std::cout << ToString(ins_type) << "\t" << (!IsCalculated(index) ? -1 : GetA(index)) << "\t";

    if (GetQk(index) != INVALID_ENTRY) {
      std::cout << "➡️" << GetQk(index) << "\t";
    } else {
      std::cout << GetVk(index) << "\t";
    }

    std::cout << entries_read_[index].GetCount() << "\t"
              << "\n";
    entries_read_.Next(index);
  }
}

}  // namespace riscv