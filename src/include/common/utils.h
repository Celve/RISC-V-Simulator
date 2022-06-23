#pragma once

#include "common/config.h"

namespace riscv {

u32 Get31To25(u32 number);

u32 Get24To20(u32 number);

u32 Get19To15(u32 number);

u32 Get14To12(u32 number);

u32 Get11To7(u32 number);

u32 Get6To0(u32 number);

u32 Get31To20(u32 number);

u32 Get31To12(u32 number);

u32 AdjoinFourHex(u32 number1, u32 number2, u32 number3, u32 number4);

u32 Extend20(u32 number);

u32 Extend11(u32 number);

u32 Extend8(u32 number);

u32 Extend16(u32 number);

u32 Extend12(u32 number);

}  // namespace riscv