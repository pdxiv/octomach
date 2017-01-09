#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <inttypes.h>

#define PARAMETER_OPCODES 15
#define OPCODES 31
#define RAM_BLOCKS 65536
#define STACK_DEPTH 16
#define Z_REGISTERS 16

char static *parameter_opcode_name[] = {
    "ADR", "GOTO", "GOTOB", "GOTOF", "IFNZADR", "IFNZGOTO", "IFNZGOTOB",
    "IFNZGOTOF", "CP*NZ", "CPZ*N", "CPZN", "ADDNZ", "CLRZ", "CPIM", "SETN"
};

char static *no_parameter_opcode_name[] = {
    "PUSHN", "POPN", "PUSHZ", "POPZ", "PUSHA", "RETN", "DUP", "DROP", "INCN",
    "DECN", "SHLN", "SHRN", "SALN", "SARN", "NOTN", "HALT"
};

struct state_struct {
    uint32_t ip;
    uint32_t no_halt;
    uint32_t stack_pointer;
    uint32_t n_register;
    uint32_t z_register[Z_REGISTERS];
    uint8_t machine_ram[RAM_BLOCKS];
    uint32_t stack_data[STACK_DEPTH];
};
typedef struct state_struct state;

void init_new_machine(state *machine_state) {
    machine_state->ip = 0;
    machine_state->no_halt = 1;
    machine_state->stack_pointer = 0;
    machine_state->n_register = 0;
    for (uint32_t t = 0; t < RAM_BLOCKS; t++) {
        machine_state->machine_ram[t] = rand() % 256;
    }
}

void print_instruction(state *machine_state, uint32_t address) {
    uint8_t opcode_head = machine_state->machine_ram[address] >> 4;
    uint8_t opcode_tail = machine_state->machine_ram[address] & 0x0f;
    printf("% 6d ", address);
    if (opcode_head < PARAMETER_OPCODES) {
        printf("%10s %2d\n", parameter_opcode_name[opcode_head], opcode_tail);
    } else {
        printf("%10s\n", no_parameter_opcode_name[opcode_tail]);
    }
}

void dump_ram_data(state *machine_state) {
    for (uint32_t t = 0; t < RAM_BLOCKS; t++) {
        print_instruction(machine_state, t);
    }
}

uint32_t run_instruction(state *machine_state) {
    uint8_t opcode_head = machine_state->machine_ram[machine_state->ip] >> 4;
    uint8_t opcode_tail = machine_state->machine_ram[machine_state->ip] & 0x0f;
    if (opcode_head < PARAMETER_OPCODES) {
        switch(opcode_head) {
            case 0 :
            case 1 :
            case 2 :
            case 3 :
            case 4 :
            case 5 :
            case 6 :
            case 7 :
            case 8 :
            case 9 :
            case 10 :
            case 11 :
            case 12 :
            case 13 :
            case 14 :
                break;
        }
    } else {
        switch(opcode_tail) {
            case 0 :
                break;
            case 1 :
                break;
            case 2 :
                break;
            case 3 :
                break;
            case 4 :
                break;
            case 5 :
                break;
            case 6 :
                break;
            case 7 :
                break;
            case 8 :
                break;
            case 9 :
                break;
            case 10 :
                break;
            case 11 :
                break;
            case 12 :
                break;
            case 13 :
                break;
            case 14 :
                break;
            case 15 :
                machine_state->no_halt = 0;
                printf("DEBUG: Halting execution at %d\n", machine_state->ip);
                break;
            default :
                break;
        }
    }
    machine_state->ip++;
}

uint32_t main(void) {
    srand(time(NULL));
    state machine_state;
    init_new_machine(&machine_state);
    // dump_ram_data(&machine_state);
    while (machine_state.no_halt) {
        run_instruction(&machine_state);
    }
    return 0;
}

// 0000LLLL    ADR        Declare L
// 0001LLLL    GOTO       Goto L unidirectional
// 0010LLLL    GOTOB      Goto L backward
// 0011LLLL    GOTOF      Goto L forward
// 0100LLLL    IFNZADR    If content of N != 0 THEN declare L
// 0101LLLL    IFNZGOTO   If content of N != 0 THEN goto L unidirectional
// 0110LLLL    IFNZGOTOB  If content of N != 0 THEN goto L backward
// 0111LLLL    IFNZGOTOF  If content of N != 0 THEN goto L forward
// 1000ZZZZ    CP*NZ      Copy content of address pointed to by N into Z
// 1001ZZZZ    CPZ*N      Copy content of Z to address pointed to by N
// 1010ZZZZ    CPZN       Copy Z into N
// 1011ZZZZ    ADDNZ      Add N with Z and store in N
// 1100ZZZZ    CLRZ       Clear Z
// 1101ZZZZ    CPIM       Copy immediate value to Z
// 1110ZZZZ    SETN       Set reference of N to Z
// 11110000    PUSHN      Push N
// 11110001    POPN       Pop N
// 11110010    PUSHZ      Push all Z
// 11110011    POPZ       Pop all Z
// 11110100    PUSHA      Push IP+1
// 11110101    RETN       Pop IP and go to address
// 11110110    DUP        Duplicate top value on stack
// 11110111    DROP       Drop top value on stack
// 11111000    INCN       Increment N
// 11111001    DECN       Decrement N
// 11111010    SHLN       Shift N left
// 11111011    SHRN       Shift N right
// 11111100    SALN       Arithmetic shift N left
// 11111101    SARN       Arithmetic shift N right
// 11111110    NOTN       Negate N
// 11111111    HALT       Stop execution
