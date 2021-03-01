#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

void save_result(char *memory_type, int block_size, int launch_count)
{
    double middle_write = 0.0;
    double middle_read = 0.0;
    double AE_write, RE_write, AE_read, RE_read;
    double *time_write = malloc(sizeof(double) * launch_count);
    double *time_read = malloc(sizeof(double) * launch_count);
    int *num = malloc(sizeof(int) * launch_count);

    FILE *time = fopen("time.dat", "r");
    for (int i = 0; i < launch_count; i++) {
        fscanf(time, "%lf %lf %d", &time_write[i], &time_read[i], &num[i]);
        middle_write += time_write[i];
        middle_read += time_read[i];
    }
    fclose(time);

    middle_write /= launch_count;
    middle_read /= launch_count;
    
    double WB = (block_size / middle_write) * 1E-3;
    double RW = (block_size / middle_read) * 1E-3;
    
    double max_write = time_write[0];
    double min_write = time_write[0];
    double max_read = time_read[0];
    double min_read = time_read[0];
    for (int i = 1; i < launch_count; i++) {
        if (time_write[i] > max_write) max_write = time_write[i];
        if (time_write[i] < min_write) min_write = time_write[i];
        if (time_read[i] > max_read) max_read = time_read[i];
        if (time_read[i] < min_read) min_read = time_read[i];
    }
    AE_write = max_write - min_write;
    RE_write = AE_write / max_write * 100;
    AE_read = max_read - min_read;
    RE_read = AE_read / max_read * 100;

    FILE *result = fopen("result.csv", "a");
    for (int i = 0; i < launch_count; i++) {
        fprintf(result, "[%s;%d;int;4;%d;wtime;%lf;%lf;%lfMb/s;%lf;%lf%%;%lf;%lf;%lfMb/s;%lf;%lf%%]\n", 
            memory_type, block_size, num[i], 
                time_write[i], middle_write, WB, AE_write, RE_write, 
                    time_read[i], middle_read, RW, AE_read, RE_read);
    }
    fclose(result);
    
    free(time_write);
    free(time_read);
    free(num);
}

void save_time(double time_write, double time_read, int num)
{
    FILE *time = fopen("time.dat", "a");
    fprintf(time, "%f %f %d\n", time_write, time_read, num);
    fclose(time);
}

void test_ram(int block_size, int launch_count)
{   
    int *memory = malloc(sizeof(int) * block_size);
    for (int i = 0; i < block_size; i++) {
        memory[i] = rand() % 201 - 100;
    }

    double time_read, time_write, sum_time_read, sum_time_write;
    for (int i = 0; i < launch_count; i++) {
        sum_time_read = 0.0;
        sum_time_write = 0.0;
        for (int j = 0; j < block_size; j++) {
            int random_number = rand() % 201 - 100;
            
            time_write = wtime();
            memory[j] = random_number;
            time_write = wtime() - time_write;
            
            time_read = wtime();
            random_number = memory[j];
            time_read = wtime() - time_read;

            sum_time_read += time_read;
            sum_time_write += time_write;
        }
        save_time(sum_time_write, sum_time_read, i);
    }
    free(memory);
}

void test_ssd(int block_size, int launch_count)
{
    double time_read, time_write, sum_time_read, sum_time_write;
    int *memory = malloc(sizeof(int) * block_size);
    
    for (int i = 0; i < block_size; i++) {
        memory[i] = rand() % 201 - 100;
    }

    for (int i = 0; i < launch_count; i++) {
        sum_time_write = 0.0;
        sum_time_read = 0.0;

        FILE *write = fopen("memory.dat", "w");
        for (int j = 0; j < block_size; j++) {
            time_write = wtime();
            fprintf(write, "%d ", memory[j]);
            time_write = wtime() - time_write;

            sum_time_write += time_write;
        }
        fprintf(write, "\n");
        fclose(write);

        FILE *read = fopen("memory.dat", "r");
        for (int j = 0; j < block_size; j++) {
            time_read = wtime();
            fscanf(read, "%d", &memory[j]);
            time_read = wtime() - time_read;

            sum_time_read += time_read;
        }
        fclose(read);
        save_time(sum_time_write, sum_time_read, i);
    }
    free(memory);
}

int main(int argc, char *argv[])
{
    if (argc != 7) {
        printf("ERROR! Not enough arguments\n");
        return 1;
    }

    int memory_type, block_size, launch_count;
    
    if ((!strcmp(argv[1], "-m")) || (!strcmp(argv[1], "--memory-type"))) {
        if (!strcmp(argv[2], "RAM")) memory_type = 0;
        else if (!strcmp(argv[2], "SSD")) memory_type = 1;
        else {
            printf("ERROR! Unknown argument: %s\n", argv[2]);
            return 1;
        }
    } else {
        printf("ERROR! Unknown key: %s\n", argv[1]);
        return 1;
    }

    if ((!strcmp(argv[3], "-b")) || (!strcmp(argv[3], "--block-size"))) {
        char arg0[10];
        strcpy(arg0, argv[4]);
        char *arg1 = strtok(argv[4], "/");
        if (strcmp(arg0, arg1)) {
            char *arg2 = strtok(NULL, "\0");
            if (!strcmp(arg2, "1Kb")) block_size = atoi(arg1) * 1024 / sizeof(int);
            else if (!strcmp(arg2, "1Mb")) block_size = atoi(arg1) * 1024 * 1024 / sizeof(int);
            else {
                printf("ERROR! Unknown dimension: %s\n", arg2);
                return 1;
            }
        } else block_size = atoi(arg1) / sizeof(int);
        if (block_size <= 0) {
            printf("ERROR! Invalid block-size\n");
            return 1;
        }
    } else {
        printf("ERROR! Unknown key: %s\n", argv[3]);
        return 1;
    }

    if ((!strcmp(argv[5], "-l")) || (!strcmp(argv[5], "--launch-count"))) {
        launch_count = atoi(argv[6]);
        if (launch_count <= 0) {
            printf("ERROR! Wrong launch-count\n");
            return 1;
        }
    } else {
        printf("ERROR! Unknown key: %s\n", argv[5]);
        return 1;
    }

    srand(time(NULL));
    if (memory_type == 0) test_ram(block_size, launch_count);
    else test_ssd(block_size, launch_count);
    save_result(argv[2], block_size, launch_count);

    return 0;
}