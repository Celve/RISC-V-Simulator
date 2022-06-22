#pragma once

#include "common/config.h"

namespace riscv {

class RISCVIns {
 public:
  virtual ~RISCVIns() = default;

  virtual void Init(u32 ins) = 0;
  virtual void Execute() = 0;

 private:
};

}  // namespace riscv