#ifndef MY_SIMPLE_COMPUTER
#define MY_SIMPLE_COMPUTER

#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

//FLAGS:
#define M 0x00000001
#define E 0x00000010
#define T 0x00000100
#define O 0x00001000
#define P 0x00010000

int memory[SIZE];
extern int correct_command[38];
int registr;

int sc_memoryInit();
int sc_memorySet(int address, int value);
int sc_memoryGet(int address, int *value);
int sc_memorySave(char *filename);
int sc_memoryLoad(char *filename);
int sc_regInit();
int sc_regSet(int flag, int value);
int sc_regGet(int flag, int *value);
int sc_commandEncode(int command, int operand, int *value);
int sc_commandDecode(int value, int *command, int *operand);

#endif