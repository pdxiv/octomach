#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <inttypes.h>

#define PARAMETER_OPCODES 15
#define OPCODES 31
#define RAM_BLOCKS 65536
#define STACK_DEPTH 16
#define Z_REGISTERS 16
#define HIGHEST_NUMBER_IN_BYTE 256
#define HIGHEST_NUMBER_IN_NYBBLE 16
#define BITS_IN_NYBBLE 4


char static *parameter_opcode_name[] = {
    "ADR", "GOTO", "GOTOB", "GOTOF", "IFNZADR", "IFNZGOTO", "IFNZGOTOB",
    "IFNZGOTOF", "CP*NZ", "CPZ*N", "CPZN", "ADDNZ", "CLRZ", "CPIM", "SETN",
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

void init_registers (state *machine_state) {
    machine_state->ip = 0;
    machine_state->no_halt = 1;
    machine_state->stack_pointer = 0;
    machine_state->n_register = 0;
}

// Randomly populate memory with populates RAM with random instructions.
// Gives equal likelyhood for an opcode to occur, independent of the number of
// bits it consists of.
void init_new_machine(state *machine_state) {
    init_registers(machine_state);
    for (uint32_t t = 0; t < RAM_BLOCKS; t++) {
        uint32_t opcode_index = rand() % OPCODES;
        uint32_t opcode_argument = rand() % HIGHEST_NUMBER_IN_NYBBLE;
        if (opcode_head < PARAMETER_OPCODES) {
            opcode_index = opcode_index << BITS_IN_NYBBLE;
            machine_state->machine_ram[t] = opcode_index + opcode_argument;            
        } else {
            opcode_index = opcode_index - PARAMETER_OPCODES;            
            machine_state->machine_ram[t] = 0b11110000 + opcode_index;
        }
    }
}

void print_instruction(state *machine_state, uint32_t address) {
    uint8_t opcode_head = machine_state->machine_ram[address] >> 4;
    uint8_t opcode_tail = machine_state->machine_ram[address] & 0x0f;
    printf("% 6d ", address);
    if (opcode_head < PARAMETER_OPCODES) {
        printf("%10s %2d\n", parameter_opcode_name[opcode_head], opcode_tail);
    } else {
        printf("%10s\n", parameter_opcode_name[opcode_tail + PARAMETER_OPCODES]);
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
            case 0 : // mnemonic: ADR, reads: [], writes: []
                break;
            case 1 : // mnemonic: GOTO, reads: [IP, RAM], writes: [IP]
                break;
            case 2 : // mnemonic: GOTOB, reads: [IP, RAM], writes: [IP]
                break;
            case 3 : // mnemonic: GOTOF, reads: [IP, RAM], writes: [IP]
                break;
            case 4 : // mnemonic: IFNZADR, reads: [N, Z], writes: []
                break;
            case 5 : // mnemonic: IFNZGOTO, reads: [IP, RAM], writes: [IP]
                break;
            case 6 : // mnemonic: IFNZGOTOB, reads: [IP, RAM], writes: [IP]
                break;
            case 7 : // mnemonic: IFNZGOTOF, reads: [IP, RAM], writes: [IP]
                break;
            case 8 : // mnemonic: CP*NZ, reads: [N, RAM, Z], writes: [Z]
                break;
            case 9 : // mnemonic: CPZ*N, reads: [N, Z], writes: [RAM]
                break;
            case 10 : // mnemonic: CPZN, reads: [N, Z], writes: [Z]
                break;
            case 11 : // mnemonic: ADDNZ, reads: [N, Z], writes: [Z]
                break;
            case 12 : // mnemonic: CLRZ, reads: [], writes: [Z]
                break;
            case 13 : // mnemonic: CPIM, reads: [], writes: [Z]
                break;
            case 14 : // mnemonic: SETN, reads: [], writes: [N]
                break;
        }
    } else {
        switch(opcode_tail) {
            case 0 : // mnemonic: PUSHN, reads: [N, SP, Z], writes: [SP, STACK]
                break;
            case 1 : // mnemonic: POPN, reads: [N, SP, STACK, Z], writes: [SP]
                break;
            case 2 : // mnemonic: PUSHZ, reads: [SP, Z], writes: [SP, STACK]
                break;
            case 3 : // mnemonic: POPZ, reads: [SP, STACK], writes: [Z]
                break;
            case 4 : // mnemonic: PUSHA, reads: [IP, SP], writes: [SP, STACK]
                break;
            case 5 : // mnemonic: RETN, reads: [SP, STACK], writes: [IP, SP]
                break;
            case 6 : // mnemonic: DUP, reads: [SP, STACK], writes: [SP, STACK]
                break;
            case 7 : // mnemonic: DROP, reads: [SP], writes: [SP]
                break;
            case 8 : // mnemonic: INCN, reads: [N, Z], writes: [Z]
                break;
            case 9 : // mnemonic: DECN, reads: [N, Z], writes: [Z]
                break;
            case 10 : // mnemonic: SHLN, reads: [N, Z], writes: [Z]
                break;
            case 11 : // mnemonic: SHRN, reads: [N, Z], writes: [Z]
                break;
            case 12 : // mnemonic: SALN, reads: [N, Z], writes: [Z]
                break;
            case 13 : // mnemonic: SARN, reads: [N, Z], writes: [Z]
                break;
            case 14 : // mnemonic: NOTN, reads: [N, Z], writes: [Z]
                break;
            case 15 : // mnemonic: HALT, reads: [], writes: [NOHALT]
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
    while (machine_state.no_halt) {
        run_instruction(&machine_state);
    }
    return 0;
}
