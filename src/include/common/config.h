#pragma once

#include <cstdint>

namespace riscv {

/**
 * @brief
 * types
 */
using u32 = unsigned;
using i32 = int;
using u8 = uint8_t;

/**
 * @brief
 * normal constnat
 */
#define REGISTER_NUMBER 32           // the number of registers
#define MEMORY_SIZE 5000000          // the size of memory
#define MAX_CHARS_PER_LINE 48        // the max line length of input string
#define REORDER_BUFFER_SIZE 32       // the size of reorder buffer
#define RESERVATION_STATION_SIZE 32  // the size of reservation station
#define LOAD_STORE_BUFFER_SIZE 32    // the size of load store buffer
#define INSTRUCTION_QUEUE_SIZE 32    // the size of instruction queue
#define QUEUE_SIZE 32                // the size of queue

#define INVALID_REORDER 0xFFFFFFFFU    // the invalid reorder number
#define INVALID_REGISTER 0xFFFFFFFFU   // the invalid register number
#define INVALID_ENTRY (-1)             // the invalid entry number
#define INVALID_IMMEDIATE 0xFFFFFFFFU  // the invalid immediate number
#define INVALID_ADDRESS 0xFFFFFFFFU    // the invalid address number

enum class TomasuloState { kUndefine, kIssue, kExecute, kWriteResult, kCommit };

}  // namespace riscv