#ifndef UTILS_H
#define UTILS_H

#define int64_t long int


void print_help();
void swap(int *a, int *b);
void print_array(const char* str, const int *arr, int len);
int read_array_from_file(const char *file_path, int** array, int *n_array);
int64_t get_system_time_us();

#endif