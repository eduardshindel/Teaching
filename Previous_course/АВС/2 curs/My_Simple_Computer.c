#include "My_Simple_Computer.h"

int correct_command[] = {0x10, 0x11, 0x20, 0x21, 0x30, 0x31, 0x32, 0x33, 0x40, 0x41, 0x42, 0x43, 0x51, 0x52, 0x53, 0x54,
                         0x55, 0x56, 0x57, 0x58, 0x59, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x70, 
                         0x71, 0x72, 0x73, 0x74, 0x75, 0x76};

int sc_memoryInit() {
    for (int i = 0; i < SIZE; i++) memory[i] = 0;
    return 0;
}

int sc_memorySet(int address, int value) {
    if ((address >= SIZE) || (address < 0)) {
        sc_regSet(M, 1);
        return 1;
    }
    if (value > 0xFFFF) return 1;
    sc_regSet(M, 0);
    memory[address] = value;
    return 0;
}

int sc_memoryGet(int address, int *value) {
    if ((address > SIZE) || (address < 0)) {
        sc_regSet(M, 1);
        return 1;
    }
    sc_regSet(M, 0);
    *value = memory[address];
    return 0;
}

int sc_memorySave(char *filename) {
    FILE *f = fopen(filename, "wb");
    fwrite(&memory, sizeof(int), SIZE, f);
    fclose(f);
    return 0;
}

int sc_memoryLoad(char *filename) {
    FILE *f = fopen(filename, "rb");
    if (!f) {
        return 1;
    } else {
        fread(memory, sizeof(int), SIZE, f);
        fclose(f);
    }
    return 0;
}

int sc_regInit() {
    registr = 0;
    return 0;
}

int sc_regSet(int flag, int value) {
    int k;
    if ((value == 0) || (value == 1)) {
        switch (flag) {
            case M:
                k = 0;
                break;
            case E:
                k = 4;
                break;
            case T:
                k = 8;
                break;
            case O:
                k = 12;
                break;
            case P:
                k = 16;
                break;
            default:
                return 1;
        }
        if (value == 1) registr = registr | (1 << k);
        else registr = registr & (~(1 << k));
        return 0;
    } else {
        return 1;
    }
}

int sc_regGet(int flag, int *value) {
    int k;
    switch (flag) {
        case M:
            k = 0;
            break;
        case E:
            k = 4;
            break;
        case T:
            k = 8;
            break;
        case O:
            k = 12;
            break;
        case P:
            k = 16;
            break;
        default:
            return 1;
    }
    *value = (registr >> k) & 0x1;
    return 0;
}

int sc_commandEncode(int command, int operand, int *value) {
    int k = 0;
    for (int i = 0; i < 38; i++) {
        if (command == correct_command[i]) {
            k = 1;
            break;
        }
    }
    if (k == 0) {
        sc_regSet(E, 1);
        return 1;
    }
    if ((operand > 0x7F) || (operand < 0)) return 1;
    *value = (command << 7) | operand;
    sc_regSet(E, 0);
    return 0;
}

int sc_commandDecode(int value, int *command, int *operand) {
    int command_1 = 0, operand_1 = 0, k = 0;

    if (value >= 0x4000) return 1;
    command_1 = command_1 | (value >> 7);
    operand_1 = value & 0x7F;

    for (int i = 0; i < 38; i++) {
        if (command_1 == correct_command[i]) {
            k = 1;
            break;
        }
    }
    if (k == 0) {
        sc_regSet(E, 1);
        return 1;
    }
    if ((operand_1 > 0x7F) || (operand_1 < 0)) return 1;
    sc_regSet(E, 0);
    *command = command_1;
    *operand = operand_1;
    return 0;
}