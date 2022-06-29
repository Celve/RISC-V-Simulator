#include "tomasulo/tomasulo_state.h"

namespace riscv {

std::string ToString(const TomasuloState &tomasulo_state) {
  switch (tomasulo_state) {
    case TomasuloState::kUndefine:
      return "Define";
    case TomasuloState::kIssue:
      return "Issue";
    case TomasuloState::kExecute:
      return "Execute";
    case TomasuloState::kWriteResult:
      return "Write";
    case TomasuloState::kCommit:
      return "Commit";
    default:
      return "Unknown";
  }
}

}  // namespace riscv