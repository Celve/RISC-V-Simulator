#include "common/utils.h"

#include "common/config.h"

namespace riscv {

u32 Get31To25(u32 number) { return (number >> 25) & 0x7F; }

u32 Get24To20(u32 number) { return (number >> 20) & 0x1F; }

u32 Get19To15(u32 number) { return (number >> 15) & 0x1F; }

u32 Get14To12(u32 number) { return (number >> 12) & 0x7; }

u32 Get11To7(u32 number) { return (number >> 7) & 0x1F; }

u32 Get6To0(u32 number) { return number & 0x7F; }

u32 Get31To20(u32 number) { return (number >> 20) & 0xFFF; }

u32 Get31To12(u32 number) { return (number >> 12) & 0xFFFFF; }

/**
 * @brief
 * basically, it would revert the four number's order
 * @return u32
 */
u32 AdjoinFourHex(u32 number1, u32 number2, u32 number3, u32 number4) {
  return (number4 << 24) | (number3 << 16) | (number2 << 8) | number1;
}

int Extend20(u32 number) {
  if ((number >> 20 & 1) != 0U) {
    return number | 0xFFE00000;
  }
  return number;
}

int Extend11(u32 number) {
  if ((number >> 11 & 1) != 0U) {
    return number | 0xFFFFF000;
  }
  return number;
}

int Extend8(u32 number) {
  if ((number >> 8 & 1) != 0U) {
    return number | 0xFFFFFF00;
  }
  return number;
}

int Extend16(u32 number) {
  if ((number >> 16 & 1) != 0U) {
    return number | 0xFFFF0000;
  }
  return number;
}

int Extend12(u32 number) {
  if ((number >> 12 & 1) != 0U) {
    return number | 0xFFFFE000;
  }
  return number;
}

}  // namespace riscv