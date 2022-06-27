#include "storage/load_store_buffer.h"

#include "storage/reservation_station.h"

namespace riscv {

void LoadStoreBufferEntry::SetA(u32 value) {
  ReservationStationEntry::SetA(value);
  calculated_ = true;
}

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
  int index = entries_write_.Front();
  if (IsCompleted(index)) {
    Init(index);
    entries_write_.PopFront();
    --ready_count_read_;
    --ready_count_write_;
    return true;
  }
  return false;
}

bool LoadStoreBuffer::IsReady(int index) {
  return entries_read_[index].IsCalculated() && entries_read_.Rank(index) < ready_count_read_;
}

void LoadStoreBuffer::Update() {
  entries_read_ = entries_write_;
  ready_count_read_ = ready_count_write_;
}

void LoadStoreBuffer::Reset() {
  while (entries_write_.Size() > ready_count_read_) {
    entries_write_.PopBack();
  }
}

}  // namespace riscv