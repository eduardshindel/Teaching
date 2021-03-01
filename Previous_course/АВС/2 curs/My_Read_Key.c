#include "My_Read_Key.h"

int rk_readkey(int *key) {
    struct termios options;
    char term[8];
    int tread;

    if (tcgetattr(0, &options) != 0) return -1;
    if (rk_mytermregime(0, 0, 1, 0, 1) != 0) return -1;
    
    tread = read(0, term, 8);
    if (tread == -1) return -1;
    term[tread] = '\0';

    if (strcmp(term, "l") == 0) *key = l;
    else if (strcmp(term, "s") == 0) *key = s;
    else if (strcmp(term, "r") == 0) *key = r;
    else if (strcmp(term, "t") == 0) *key = t;
    else if (strcmp(term, "i") == 0) *key = i;
    else if (strcmp(term, "q") == 0) *key = q;
    else if (strcmp(term, "\E[15~") == 0) *key = f5;
    else if (strcmp(term, "\E[17~") == 0) *key = f6;
    else if (strcmp(term, "\E[A") == 0) *key = up;
    else if (strcmp(term, "\E[B") == 0) *key = down;
    else if (strcmp(term, "\E[D") == 0) *key = left;
    else if (strcmp(term, "\E[C") == 0) *key = right;
    else if (strcmp(term, "\n") == 0) *key = enter;
    else return -1;

    if (tcsetattr(0, TCSANOW, &options) != 0) return -1;

    return 0;
}

int rk_mytermsave() {
    struct termios options;
    if (tcgetattr(0, &options) != 0) return -1;
    
    FILE *file = fopen("termsettings.txt", "wb");
    if (file == NULL) return -1;

    fwrite(&options, sizeof(options), 1, file);
	fclose(file);
	
	return 0;
}

int rk_mytermrestore() {
    struct termios options;

    FILE *file = fopen("termsettings.txt", "rb");
    if (file == NULL) return -1;

    if (fread(&options, sizeof(options), 1, file) > 0) {
        if (tcsetattr(0, TCSAFLUSH, &options) != 0) return -1;
    } else return -1;
    fclose(file);

    return 0;
}

int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint) {
    struct termios options;

    if (tcgetattr(0, &options) != 0) return -1;

    if (regime == 1) options.c_lflag |= ICANON;
    else if (regime == 0) options.c_lflag &= ~ICANON;
    else return -1;

    if (regime == 0) {
        options.c_cc[VTIME] = vtime;
		options.c_cc[VMIN] = vmin;
        
        if (echo == 1) options.c_lflag |= ECHO;
        else if (echo == 0) options.c_lflag &= ~ECHO;
        else return -1;

        if (sigint == 1) options.c_lflag |= ISIG;
        else if (sigint == 0) options.c_lflag &= ~ISIG;
        else return 0;
    }
    if (tcsetattr(0, TCSANOW, &options) != 0) return -1;

    return 0;
}