#include "storage/reservation_station.h"

#include <cstring>
#include <iostream>

#include "common/config.h"

namespace riscv {

ReservationStationEntry::ReservationStationEntry() {
  ins_ = RiscvIns();
  Init();
}

void ReservationStationEntry::Init() {
  MakeNoBusy();
  SetQj(INVALID_ENTRY);
  SetQk(INVALID_ENTRY);
  SetDest(INVALID_ENTRY);
}

int ReservationStation::Available() {
  for (int i = 0; i < RESERVATION_STATION_SIZE; i++) {
    if (!entries_write_[i].IsBusy()) {
      ++size_write_;
      return i;
    }
  }
  return INVALID_ENTRY;
}

void ReservationStation::Init(int index) { entries_write_[index].Init(); }

int ReservationStation::FindReady() {
  for (int i = 0; i < RESERVATION_STATION_SIZE; i++) {
    if (entries_read_[i].IsBusy() && entries_read_[i].IsReady()) {
      return i;
    }
  }
  return INVALID_ENTRY;
}

void ReservationStation::GetNext(int &index) {
  if (++index == RESERVATION_STATION_SIZE) {
    index = INVALID_ENTRY;
  }
}

void ReservationStation::Pop(int index) {
  if (index == INVALID_ENTRY) {
    return;
  }
  entries_write_[index].Init();
  --size_write_;
}

void ReservationStation::Update() {
  memcpy(entries_read_, entries_write_, sizeof(entries_read_));
  size_read_ = size_write_;
}

void ReservationStation::Reset() {
  for (auto &i : entries_write_) {
    i.Init();
  }
  size_write_ = 0;
}

void ReservationStation::Print() {
  std::cout << "Reservation Station😉: " << std::endl;
  std::cout << "id\tins\trs\trt\trob\n";
  for (int i = 0; i < RESERVATION_STATION_SIZE; i++) {
    if (!entries_read_[i].IsBusy()) {
      continue;
    }
    auto ins = GetIns(i);
    std::cout << i << "\t" << ToString(ins.GetInsType()) << "\t";
    if (GetQj(i) == INVALID_ENTRY) {
      std::cout << int(GetVj(i)) << "\t";
    } else {
      std::cout << "➡️" << int(GetQj(i)) << "\t";
    }
    if (GetQk(i) == INVALID_ENTRY) {
      std::cout << int(GetVk(i)) << "\t";
    } else {
      std::cout << "➡️" << int(GetQk(i)) << "\t";
    }
    std::cout << int(GetDest(i)) << std::endl;
  }
}

}  // namespace riscv