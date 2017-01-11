# octomach
Simple virtual machine for genetic algorithm experiments.
## Registers/memory
Register/memory | Function
-------- | --------
IP | Instruction pointer
Z0 - Z15 | Accumulator registers
N | Accumulator reference register
SP | Stack pointer
NOHALT | Halts the machine if set to 0
RAM | Main random access storage

## Instruction set
Opcode | Mnemonic | Description | Reads | Writes
------ | -------- | ----------- | ----- | ------
0000LLLL | ADR | Declare L | |
0001LLLL | GOTO | Goto L unidirectional | IP, RAM | IP
0010LLLL | GOTOB | Goto L backward | IP, RAM | IP
0011LLLL | GOTOF | Goto L forward | IP, RAM | IP
0100LLLL | IFNZADR | If content of N != 0 THEN declare L | N, Z |
0101LLLL | IFNZGOTO | If content of N != 0 THEN goto L unidirectional | IP, RAM | IP
0110LLLL | IFNZGOTOB | If content of N != 0 THEN goto L backward | IP, RAM | IP
0111LLLL | IFNZGOTOF | If content of N != 0 THEN goto L forward | IP, RAM | IP
1000ZZZZ | CP\*NZ | Copy content of address pointed to by N into Z | N, RAM, Z | Z
1001ZZZZ | CPZ\*N | Copy content of Z to address pointed to by N | N, Z | RAM
1010ZZZZ | CPZN | Copy Z into N | N, Z | Z
1011ZZZZ | ADDNZ | Add N with Z and store in N | N, Z | Z
1100ZZZZ | CLRZ | Clear Z | | Z
1101ZZZZ | CPIM | Copy immediate value to Z | | Z
1110ZZZZ | SETN | Set reference of N to Z | | N
11110000 | PUSHN | Push N | N, SP, Z | SP, STACK
11110001 | POPN | Pop N | N, SP, STACK, Z | SP
11110010 | PUSHZ | Push all Z | SP, Z | SP, STACK
11110011 | POPZ | Pop all Z | SP, STACK | Z
11110100 | PUSHA | Push IP+1 | IP, SP | SP, STACK
11110101 | RETN | Pop IP and go to address | SP, STACK | IP, SP
11110110 | DUP | Duplicate top value on stack | SP, STACK | SP, STACK
11110111 | DROP | Drop top value on stack | SP | SP
11111000 | INCN | Increment N | N, Z | Z
11111001 | DECN | Decrement N | N, Z | Z
11111010 | SHLN | Shift N left | N, Z | Z
11111011 | SHRN | Shift N right | N, Z | Z
11111100 | SALN | Arithmetic shift N left | N, Z | Z
11111101 | SARN | Arithmetic shift N right | N, Z | Z
11111110 | NOTN | Negate N | N, Z | Z
11111111 | HALT | Stop execution | |
