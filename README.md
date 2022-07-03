# 👋About this

This is a RISC-V simulator which simulates some basic infrastructure of a RISC-V processor. It's implemented in tomasulo algorithm.

# 🛞Architecture

## Instruction Queue

The instruction queue is abandoned due to the bug introduced by JALR instruction. The pre-fetch of JALR in instruction queue might get wrong.

It takes one cycle to fetch a instruction from memory.

With branch instruction, a branch prediction is done inside the instruction queue to get the right pc. However, the JALR instruction needs register which should be done in the reservation stations. Therefore, the instruction queue has to pre-fetch the register.

## Reservation Stations

The instruction gets into the reservation stations after popup from the instruction queue. It would be flagged "Issued".

In this stage, it would be sent to the arithmetic logic units for computation. The result would be written into common data bus.

## Load and Store Buffer

Used to load and store with memory. 

## Common Data Bus

Used to transfer information between hardwares. 

## Reorder Buffer

Record information with register reordering. 

# 🪄Prediction Result

|    Testcase    |  Cycles   | Two-bit saturated | Two-level adaptive |
| :------------: | :-------: | :---------------: | :----------------: |
|  array_test1   |    295    |        50%        |       54.55%       |
|  array_test2   |    360    |      46.15%       |        50%         |
|     qsort      |  2245812  |      87.42%       |       95.22%       |
|     queens     |  1256639  |      73.39%       |       74.56%       |
| manyarguments  |    83     |      80.00%       |       80.00%       |
|     magic      |  981569   |      78.40%       |       85.13%       |
|   basicopt1    |  801340   |      82.40%       |       88.24%       |
|   bulgarian    |  695409   |      94.44%       |       94.26%       |
|    lvalue2     |    73     |      66.67%       |       66.67%       |
|   multiarray   |   3070    |      79.01%       |       53.08%       |
| statement_test |   1799    |      64.36%       |       63.37%       |
|      tak       |  2921136  |      73.80%       |       83.60%       |
|       pi       | 136812050 |      82.40%       |       83.85%       |
|     hanoi      |  369717   |      61.09%       |       87.18%       |
|      expr      |    835    |      82.89%       |       72.97%       |
|      gcd       |    734    |      67.50%       |       62.50%       |
|   superloop    |  680834   |      93.82%       |       97.35%       |
|     naive      |    40     |      100.00%      |      100.00%       |

