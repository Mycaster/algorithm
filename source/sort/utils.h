#ifndef UTILS_H
#define UTILS_H

#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define int64_t long int


void swap(int *a, int *b);
void print_array(const char* str, const int *arr, int len);
int read_array_from_file(const char *file_path, int** array, int *n_array);
int64_t get_system_time_us();


//simple log api
void set_log_level(int level);
int get_log_level();
#define LOGTRACE(fmt, ...)  do                                                          \
{                                                                                       \
    if (get_log_level())                                                                 \
        printf("%s:%d func(%s): "fmt"\n", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__); \
}while(0)                
#endif