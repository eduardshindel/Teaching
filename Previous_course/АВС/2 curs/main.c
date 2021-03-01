#include "main.h"

void print_memory() {
    int count = 0;
    
    mt_gotoXY(2, 9);
    for (int i = 0; i < SIZE; i++) {
        if (memory[i] >= 0x4000) printf("-%04X\t", memory[i]);
        else printf("+%04X\t", memory[i]);
        count++;
        if (count == 10) {
            printf("\n\t");
            count = 0;
        }
    }
}

void print_accumulator() {
    mt_setfgcolor(white);
    mt_gotoXY(2, 101);
    (accumulator >= 0x4000) ? printf("-%04X\t", accumulator) : printf("+%04X\t", accumulator);
}

void select_number(int number, int *big) {
    switch (number) {
        case 0:
            big[0] = zero[0];
            big[1] = zero[1];
            break;
        case 1:
            big[0] = one[0];
            big[1] = one[1];
            break;
        case 2:
            big[0] = two[0];
            big[1] = two[1];
            break;
        case 3:
            big[0] = three[0];
            big[1] = three[1];
            break;
        case 4:
            big[0] = four[0];
            big[1] = four[1];
            break;
        case 5:
            big[0] = five[0];
            big[1] = five[1];
            break;
        case 6:
            big[0] = six[0];
            big[1] = six[1];
            break;
        case 7:
            big[0] = seven[0];
            big[1] = seven[1];
            break;
        case 8:
            big[0] = eight[0];
            big[1] = eight[1];
            break;
        case 9:
            big[0] = nine[0];
            big[1] = nine[1];
            break;
        case 10:
            big[0] = bigA[0];
            big[1] = bigA[1];
            break;
        case 11:
            big[0] = bigB[0];
            big[1] = bigB[1];
            break;
        case 12:
            big[0] = bigC[0];
            big[1] = bigC[1];
            break;
        case 13:
            big[0] = bigD[0];
            big[1] = bigD[1];
            break;
        case 14:
            big[0] = bigE[0];
            big[1] = bigE[1];
            break;
        case 15:
            big[0] = bigF[0];
            big[1] = bigF[1];
            break;
        default:
            break;
    }
}

void print_instruction_counter() {
    mt_setfgcolor(white);
    mt_gotoXY(5, 101);
    printf("+%04X", inst_counter);

    bc_box(13, 7, 22, 54);
    int i_count = memory[inst_counter];
    if (i_count < 0) bc_printbigchar(minus, 13, 7, white, black);
    else bc_printbigchar(plus, 13, 7, white, black);
    int *big = malloc(sizeof(int) * 2);

    int number = i_count % 16;
    i_count /= 16;
    select_number(number, big);
    bc_printbigchar(big, 13, 45, white, black);

    number = i_count % 16;
    i_count /= 16;
    select_number(number, big);
    bc_printbigchar(big, 13, 35, white, black);

    number = i_count % 16;
    i_count /= 16;
    select_number(number, big);
    bc_printbigchar(big, 13, 25, white, black);

    number = i_count % 16;
    select_number(number, big);
    bc_printbigchar(big, 13, 15, white, black);
}

void print_opertion() {
    int value = memory[inst_counter];
    int command = 0, operand = 0;
    mt_gotoXY(8, 99);
    sc_commandDecode(value, &command, &operand);
    mt_setfgcolor(white);
    printf("+%02X : %02X\n", command, operand);
}

void print_flags() {
    int m, e, t, o, p;

    sc_regGet(M, &m);
    sc_regGet(E, &e);
    sc_regGet(T, &t);
    sc_regGet(O, &o);
    sc_regGet(P, &p);

    mt_gotoXY(11, 93);
    if (m == 1) mt_setfgcolor(red);
    else mt_setfgcolor(green);
    printf("M");

    mt_gotoXY(11, 98);
    if (e == 1) mt_setfgcolor(red);
    else mt_setfgcolor(green);
    printf("E");

    mt_gotoXY(11, 103);
    if (t == 1) mt_setfgcolor(red);
    else mt_setfgcolor(green);
    printf("T");

    mt_gotoXY(11, 108);
    if (o == 1) mt_setfgcolor(red);
    else mt_setfgcolor(green);
    printf("O");

    mt_gotoXY(11, 113);
    if (p == 1) mt_setfgcolor(red);
    else mt_setfgcolor(green);
    printf("P");
}

void print_keys() {
    mt_setfgcolor(white);
    mt_gotoXY(14, 58);
    printf("l - load\n");
    mt_gotoXY(15, 58);
    printf("s - save\n");
    mt_gotoXY(16, 58);
    printf("r - run\n");
    mt_gotoXY(17, 58);
    printf("t - step\n");
    mt_gotoXY(18, 58);
    printf("i - reset\n");
    mt_gotoXY(19, 58);
    printf("f5 - accumulator\n");
    mt_gotoXY(20, 58);
    printf("f6 - instructionCounter\n");
}

void active_window() {
    int x = 2 + (inst_counter / 10);
    int y = 9 + (inst_counter % 10) * 8;

    mt_gotoXY(x, y);
    mt_setfgcolor(black);
    mt_setbgcolor(white);
    (memory[inst_counter] >= 0x4000) ? printf("-%04X\t", memory[inst_counter]) : printf("+%04X\t", memory[inst_counter]);
    mt_setfgcolor(white);
    mt_setbgcolor(black);
}

void print_boxes() {
    bc_box(1, 7, 12, 87);
    mt_gotoXY(0, 44);
    mt_setfgcolor(yellow);
    printf(" Memory \n");
    mt_setfgcolor(white);

    bc_box(1, 88, 3, 119);
    mt_gotoXY(0, 97);
    mt_setfgcolor(yellow);
    printf(" accumulator \n");

    bc_box(4, 88, 6, 119);
    mt_gotoXY(4, 94);
    mt_setfgcolor(yellow);
    printf(" instructionCounter \n");

    bc_box(7, 88, 9, 119);
    mt_gotoXY(7, 98);
    mt_setfgcolor(yellow);
    printf(" Operation \n");

    bc_box(10, 88, 12, 119);
    mt_gotoXY(10, 100);
    mt_setfgcolor(yellow);
    printf(" Flags \n");

    bc_box(13, 55, 22, 119);
    mt_gotoXY(13, 67);
    mt_setfgcolor(yellow);
    printf(" Keys: \n");
}

void print_info(int count) {
    print_memory();
    print_opertion();
    print_flags();
    active_window();
    print_accumulator();
    print_instruction_counter();
    mt_gotoXY(23, 7);
    printf("Input/Output:\n");
    for (int i = 0; i < count; i++) printf("\n");
}

void next_step() {
    inst_counter++;
}

int main()
{
    char filename[32];
    int value;
    int command = 0, operand = 0;
    int ch;

    mt_clrscr();
    print_boxes();
    print_keys();
    
    while (1) {
        value = 0;         
        print_info(count);
        rk_readkey(&ch);
        rk_mytermregime(0, 0, 1, 0, 1);
        switch (ch) {
            case up:
                if (inst_counter <= 9) break;
                inst_counter -= 10;
                break;
            case down:
                if (inst_counter >= 90) break;
                inst_counter += 10;
                break;
            case left:
                if (inst_counter % 10 == 0) break;
                inst_counter--;
                break;
            case right:
                if ((inst_counter + 1) % 10 == 0) break;
                inst_counter++;
                break;
            case l:
                rk_mytermregime(0, 0, 1, 1, 1);
                printf("\t> ");
                scanf("%s", filename);
                sc_memoryLoad(filename);
                count++;
                rk_mytermregime(0, 0, 1, 0, 1);
                break;
            case s:
                rk_mytermregime(0, 0, 1, 1, 1);
                printf("\t> ");
                scanf("%s", filename);
                sc_memorySave(filename);
                count++;
                rk_mytermregime(0, 0, 1, 0, 1);
                break;
            case enter:
                rk_mytermregime(0, 0, 1, 1, 1);
                printf("\t> ");
                scanf("%x", &value);
                sc_memorySet(inst_counter, value);
                count++;
                rk_mytermregime(0, 0, 1, 0, 1);
                break;
            case r:
                sc_regSet(T, 1);
                while (!CU()) print_info(count);
                sc_regSet(T, 0);
                break;
            case i:
                sc_memoryInit();
                sc_regInit();
                inst_counter = 0;
                accumulator = 0;
                break;
            case f5:
                rk_mytermregime(0, 0, 1, 1, 1);
                printf("\t> ");
                scanf("%x", &value);
                accumulator = value;
                count++;
                rk_mytermregime(0, 0, 1, 0, 1);
                break;
            case f6:
                rk_mytermregime(0, 0, 1, 1, 1);
                printf("\t> ");
                scanf("%x", &value);
                inst_counter = value;
                count++;
                rk_mytermregime(0, 0, 1, 0, 1);
                break;
            case t:
                CU();
                break;
            case q:
                rk_mytermregime(0, 0, 1, 1, 1);
                return 0;
            default:
                break;
        }
        if (count == 10) {
            mt_clrscr();
            print_boxes();
            print_keys();
            count = 0;
        }
    }
}