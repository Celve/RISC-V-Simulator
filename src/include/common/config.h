#pragma once

namespace riscv {

/**
 * @brief
 * types
 */
using u32 = unsigned;
using i32 = int;

/**
 * @brief
 * normal constnat
 */
#define REGISTER_NUMBER 32            // the number of registers
#define MEMORY_SIZE 5000000           // the size of memory
#define MAX_CHARS_PER_LINE 48         // the max line length of input string
#define REORDER_BUFFER_SIZE 32        // the size of reorder buffer
#define RESERVATION_STATION_SIZE 32   // the size of reservation station
#define INVALID_REORDER 0xFFFFFFFFU   // the invalid reorder number
#define INVALID_REGISTER 0xFFFFFFFFU  // the invalid register number

}  // namespace riscv