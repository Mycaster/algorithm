#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "insert_sort.h"
#include "quick_sort.h"
#include "heap_sort.h"
#include "kth.h"


typedef enum ALGORITHM_TYPE
{
  INSERT_SORT = 1,
  QUICK_SORT = 2,
  QUICK_SORT2 = 3,
  HEAP_SORT = 4
}ALGORITHM_TYPE;
typedef int(*sort_function)(int *array, int len);
typedef struct sort_func_map
{
  ALGORITHM_TYPE type;
  char * algorithm_name;
  sort_function func;
}sort_func_map;


static int k = 0;
static int show_detail = 0;
static int algorithm = 0;
static char *file_path = NULL;
static sort_func_map s_func_map[]=
{
  {INSERT_SORT, "插入排序", insert_sort},
  {QUICK_SORT , "快速排序[尾元素作为主元]", quick_sort},
  {QUICK_SORT2, "快速排序[随机主元]", random_quick_sort},
  {HEAP_SORT  , "堆排序" ,  heap_sort},
};
static size_t s_func_map_size = sizeof(s_func_map)/sizeof(s_func_map[0]);



int main(int argc, char *argv[])
{
    int opt;
    while((opt =getopt(argc,argv,"t:f:dk:"))!= -1)
    {
      switch (opt) 
      {
        case 't':
          algorithm = atoi(optarg);
          break;
        case 'f':
          file_path = optarg;
          break;
        case 'd':
          show_detail = 1;
          break;
        case 'k':
          k = atoi(optarg);
          break;
        case '?':
          print_help();
          break;
      }
    }
    if (file_path==NULL)
      file_path = "./testdata.txt"; 
    
    int*test_array = NULL;
    int len = 0;
    int ret = read_array_from_file(file_path, &test_array, &len);
    if (ret != 0)
    {
      return 0;
    }
    if (show_detail)
    {
      print_array("input array:", test_array, len);
      printf("\n\n");
    }


    kth(test_array, len , k);
    
    int find = 0;
    int64_t start = 0;
    int64_t end = 0;
    for (int i = 0; i < s_func_map_size; i++)
    {
      if ((int)s_func_map[i].type == algorithm)
      {
        find = 1;
        start = get_system_time_us();
        s_func_map[i].func(test_array, len);
        end = get_system_time_us();
        printf("%s, 数组大小[%d], 耗时[%ld 微秒]\n", s_func_map[i].algorithm_name, len, end - start);
        break;
      }
    }
    if (show_detail)
    {
      print_array("", test_array, len);
    }
    if (!find)
    {
      printf("not find sort_function, type=%d\n", algorithm);
      print_help();
    }
    return 0;
}