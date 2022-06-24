#include <cstdio>
#include <cstring>
#include <iostream>

#include "common/config.h"
#include "common/utils.h"
#include "instruction/riscv_ins.h"
#include "storage/memory.h"
#include "storage/registers.h"
#include "storage/tomasulo.h"

char hexs[MAX_CHARS_PER_LINE];
riscv::Storage *storage;

void SetUp() { storage = new riscv::Storage; }

void TearDown() { delete storage; }

void Input() {
  int hex_cursor;
  while (scanf("%s", hexs) != EOF) {
    if (hexs[0] == '@') {
      // indicate the start point of the program
      sscanf(hexs, "@%x", &hex_cursor);
      // the sentence can be used for debug
      // printf("start point is: %x\n", hex_cursor);
    } else {
      // the body of the program
      int n = strlen(hexs);
      for (int i = 0; i < n; i += 3) {
        riscv::u32 hex;
        sscanf(hexs, "%x", &hex);
        storage->GetMemory()->SetByte(hex_cursor++, hex);
        // the sentence can be used for debug
        // printf("put %x in %d\n", hex, hex_cursor);
      }
    }
  }
}

void Execute() {
  while (true) {
    // fetch instruction
    auto pc = storage->GetRegs()->GetPc();

    auto ins_hex = storage->GetMemory()->GetWord(pc);
    if (ins_hex == 0xFF00513) {
      printf("%u\n", storage->GetRegs()->GetReg(10) & 0xFFU);
      break;
    }

    // decode
    riscv::RiscvIns *ins = riscv::GenerateIns(ins_hex, storage);

    // execute
    ins->Execute();

    // TODO(celve): memory related and write-back

    // tear down
    delete ins;

    regs->Next();
  }
}

int main() {
  SetUp();
  Input();
  Execute();
  TearDown();
}