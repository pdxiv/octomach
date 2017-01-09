# octomach
Simple virtual machine for genetic algorithm experiments.
## Instruction set

Opcode | Mnemonic | Description
------ | -------- | -----------
0000LLLL | ADR | Declare L
0001LLLL | GOTO | Goto L unidirectional
0010LLLL | GOTOB | Goto L backward
0011LLLL | GOTOF | Goto L forward
0100LLLL | IFNZADR | If content of N != 0 THEN declare L
0101LLLL | IFNZGOTO | If content of N != 0 THEN goto L unidirectional
0110LLLL | IFNZGOTOB | If content of N != 0 THEN goto L backward
0111LLLL | IFNZGOTOF | If content of N != 0 THEN goto L forward
1000ZZZZ | CP\*NZ | Copy content of address pointed to by N into Z
1001ZZZZ | CPZ\*N | Copy content of Z to address pointed to by N
1010ZZZZ | CPZN | Copy Z into N
1011ZZZZ | ADDNZ | Add N with Z and store in N
1100ZZZZ | CLRZ | Clear Z
1101ZZZZ | CPIM | Copy immediate value to Z
1110ZZZZ | SETN | Set reference of N to Z
11110000 | PUSHN | Push N
11110001 | POPN | Pop N
11110010 | PUSHZ | Push all Z
11110011 | POPZ | Pop all Z
11110100 | PUSHA | Push IP+1
11110101 | RETN | Pop IP and go to address
11110110 | DUP | Duplicate top value on stack
11110111 | DROP | Drop top value on stack
11111000 | INCN | Increment N
11111001 | DECN | Decrement N
11111010 | SHLN | Shift N left
11111011 | SHRN | Shift N right
11111100 | SALN | Arithmetic shift N left
11111101 | SARN | Arithmetic shift N right
11111110 | NOTN | Negate N
11111111 | HALT | Stop execution

