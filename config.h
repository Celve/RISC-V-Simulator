
#pragma once

#include <atomic>

#include "Account.h"
#include "TrainSystem.h"

namespace thomas {

static constexpr int INVALID_PAGE_ID = -1;                                    // invalid page id
static constexpr int INVALID_TXN_ID = -1;                                     // invalid transaction id
static constexpr int INVALID_LSN = -1;                                        // invalid log sequence number
static constexpr int HEADER_PAGE_ID = 0;                                      // the header page id
static constexpr int PAGE_SIZE = 32768;                                       // size of a data page in byte
static constexpr int BUFFER_POOL_SIZE = 1024;                                 // size of buffer pool
static constexpr int THREAD_NUMBER = 1;                                       // size of thread number
static constexpr int MUTEX_NUMBER = 8192;                                     // size of mutex number
static constexpr int LOG_BUFFER_SIZE = ((BUFFER_POOL_SIZE + 1) * PAGE_SIZE);  // size of a log buffer in byte
static constexpr int BUCKET_SIZE = 50;                                        // size of extendible hash bucket

using int32_t = int;
using uint16_t = unsigned short;  // NOLINT

using frame_id_t = int32_t;         // frame id type
using page_id_t = int32_t;          // page id type
using txn_id_t = int32_t;           // transaction id type
using lsn_t = int32_t;              // log sequence number type
using slot_offset_t = std::size_t;  // slot offset type
using oid_t = uint16_t;

}  // namespace thomas
