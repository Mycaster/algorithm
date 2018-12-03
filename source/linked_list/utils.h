#ifndef UTILS_H
#define UTILS_H

#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct ListNode
{
    int value;
    struct ListNode *next;
}ListNode;

struct list_op
{
  int   (*init)();
  int   (*run)();
  const char* (*print_before)();
  const char* (*print_after)();
};

void delete_list_node(ListNode* node);
ListNode* create_list(int *arr, int len);
int insert_node(ListNode *head, int value, int position);
int delete_node(ListNode *head, int value);
const char* print_list(ListNode *head);

int64_t get_system_time_us();
int read_array_from_file(const char *file_path, int** array, int *n_array, int line);

#endif