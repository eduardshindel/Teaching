#ifndef MAIN_H
#define MAIN_H

#include "My_Simple_Computer.h"
#include "My_Term.h"
#include "My_Big_Chars.h"
#include "My_Read_Key.h"
#include "cpu.h"
#include <signal.h>

void print_memory();
void print_accumulator();
void select_number(int number, int *big);
void print_instruction_counter();
void print_opertion();
void print_flags();
void print_keys();
void active_window();
void print_boxes();
void print_info(int count);
void next_step();

#endif