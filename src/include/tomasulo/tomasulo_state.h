#include <string>

namespace riscv {

enum class TomasuloState { kUndefine, kIssue, kExecute, kWriteResult, kCommit };

std::string ToString(const TomasuloState &tomasulo_state);

}  // namespace riscv