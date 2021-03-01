#include "cpu.h"
#include "My_Read_Key.h"
#include "main.h"

int inst_counter = 0;
int accumulator = 0;
int count = 0;

int CU() {
    int value = 0;
	int command = 0;
	int operand = 0;

	sc_memoryGet(inst_counter, &value);

	if (sc_commandDecode(value, &command, &operand)) {
		sc_regSet(E, 1);
		sc_regSet(T, 0);
		return 1;
	}
    if (command >= 0x30 && command <= 0x33) {
        next_step();
        ALU(command, operand);
	} else {
        switch (command) {
            case READ:
				rk_mytermregime(0, 0, 1, 1, 1);
				printf("\t> ");
				int value;
             	scanf("%d", &value);
				rk_mytermregime(0, 0, 1, 0, 1);
				if (value > 0x7FFF) return 1;
                if (value <= 0) value = (-value) + 0x4000;
				sc_memorySet(operand, value);
				next_step();
                count++;
				break;
			case WRITE:
				printf("\t< ");
				sc_memoryGet(operand, &value);
                if (value >= 0x4000) value = value & 0x1FFF;
				printf("%d\n", value);
				next_step();
                count++;
				break;
			case LOAD:
				sc_memoryGet(operand, &accumulator);
				next_step();
				break;
			case STORE:
				sc_memorySet(operand, accumulator);
				next_step();
				break;
			case JUMP:
				if ((operand < 0) || (operand > 0x63 )) {
					sc_regSet(M, 1);
					return 1;
				}
				inst_counter = operand;
				break;
			case JNEG:
				if ((accumulator >> 14) == 1) {
					if (((accumulator >> 13 ) & 1) == 1) {
						if (operand > 0x63) {
							sc_regSet(M, 1);
							return 1;
						} else inst_counter = operand;
					} else next_step();
				} else next_step();
				break;
			case JZ:
				if ((accumulator >> 14) == 1) {
					if (((accumulator >> 13) & 1) == 0) {
						if ((accumulator & 0x1FFF) == 0){
							if (operand > 0x63) {
								sc_regSet(M, 1);
								return 1;
							} else inst_counter = operand;
						} else next_step();
					} else next_step();
				} else next_step();
				break;
			case HALT:
				return 1;
            case XOR:
                sc_memoryGet(operand, &value);
                accumulator ^= value;
                next_step();
                break;
        }
    }
	return 0;
}

int ALU(int command, int operand) {
    int value;
    sc_memoryGet(operand, &value);

    switch (command) {
        case ADD:
            if (((value >> 14) == 1) && ((accumulator >> 14) == 1)) {
                int b = (value >> 13) & 1;
                int a = (accumulator >> 13) & 1;
                if (a == b) {
                    if ((accumulator & 0x1FFF) + (value & 0x1FFF) > 0x1FFF) {
                        sc_regSet(P, 1);
                        return -1;
                    } else accumulator = (accumulator & 0x1FFF) + (value & 0x1FFF) + (1 << 14) + (a << 13);
                } else {
                    if ((accumulator & 0x1FFF) > (value & 0x1FFF)) {
                        accumulator = (accumulator & 0x1FFF) - (value & 0x1FFF) + (1 << 14) + (a << 13);
                    } else if ((accumulator & 0x1FFF) < (value & 0x1FFF)) {
                        accumulator = (value & 0x1FFF) - (accumulator & 0x1FFF) + (1 << 14) + (b << 13);
                    } else if ((accumulator & 0x1FFF) == (value & 0x1FFF)) {
                        accumulator = (value & 0x1FFF) - (accumulator & 0x1FFF) + (1 << 14);
                    }
                }
            } else return -1;
            break;
        case SUB:
            if ((value >> 14) == 1 && (accumulator >> 14 == 1)) {
                int a = accumulator >> 13 & 1;
                int b = value >> 13 & 1;
                if (a == b) {
                    if (b == 0) b = 1;
                    else b = 0;
                    if ((accumulator & 0x1FFF) > (value & 0x1FFF)) {
                        accumulator = (accumulator & 0x1FFF) - (value & 0x1FFF) + (1 << 14) + (a << 13);
                    } else if ((accumulator & 0x1FFF) < (value & 0x1FFF)) {
                        accumulator = (value & 0x1FFF) - (accumulator & 0x1FFF) + (1 << 14) + (b << 13);
                    } else if ((accumulator & 0x1FFF) == (value & 0x1FFF)) {
                        accumulator = (value & 0x1FFF) - (accumulator & 0x1FFF) + (1 << 14);
                    }
                } else {
                    if ((accumulator & 0x1FFF) + (value & 0x1FFF) > 0x1FFF) {
                        sc_regSet(P, 1);
                        return -1;
                    } else accumulator = (accumulator & 0x1FFF) + (value & 0x1FFF) + (1 << 14) + (a << 13);
                }
            } else return -1;
            break;
        case DIVIDE:
            if ((value >> 14 == 1) && (accumulator >> 14 == 1)) {
                if ((value & 0x1FFF) == 0) {
                    sc_regSet(O, 1);
                    return -1;
                } else if (((value >> 13) & 1) == ((accumulator >> 13) & 1)) {
                    accumulator = (accumulator & 0x1FFF) / (value & 0x1FFF) + (1 << 14);
                } else accumulator = (accumulator & 0x1FFF) / (value & 0x1FFF) + (1 << 13) + (1 << 14);
            } else return -1;
            break;
        case MUL:
            if ((value >> 14 == 1) && (accumulator >> 14 == 1)) {
                if ((accumulator & 0x1FFF) * (value & 0x1FFF) > 0x1FFF) {
                    sc_regSet(P, 1);
                    return -1;
                } else if ((accumulator >> 13 & 1) == (value >> 13 & 1)) {
                    accumulator = (accumulator & 0x1FFF) * (value & 0x1FFF) + (1 << 14);
                } else accumulator = (accumulator & 0x1FFF) * (value & 0x1FFF) + (1 << 14) + (1 << 13);
            } else return -1;
    }
    return 0;
}