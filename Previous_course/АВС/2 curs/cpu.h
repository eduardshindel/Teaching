#ifndef CPU_H
#define CPU_H

#include "My_Simple_Computer.h"
#include "My_Term.h"
#include <stdio.h>

extern int inst_counter;
extern int accumulator;
extern int count;

#define READ 0x10
#define WRITE 0x11

#define LOAD 0x20
#define STORE 0x21

#define ADD 0x30
#define SUB 0x31
#define DIVIDE 0x32
#define MUL 0x33

#define JUMP 0x40
#define JNEG 0x41
#define JZ 0x42
#define HALT 0x43

#define XOR 0x54

int CU();
int ALU(int command, int operand);

#endif