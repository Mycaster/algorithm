#include "utils.h"
#include "insert_sort.h"
#include "select_sort.h"
#include "quick_sort.h"
#include "heap_sort.h"
#include "kth.h"

typedef enum ALGORITHM_TYPE
{
  INSERT_SORT = 1,
  SELECT_SORT = 2,
  QUICK_SORT = 3,
  QUICK_SORT2 = 4,
  HEAP_SORT = 5
}ALGORITHM_TYPE;
typedef int(*sort_function)(int *array, int len);
typedef struct sort_func_map
{
  ALGORITHM_TYPE type;
  char * algorithm_name;
  sort_function func;
}sort_func_map;

static sort_func_map s_func_map[]=
{
  {INSERT_SORT, "插入排序", insert_sort},
  {SELECT_SORT, "选择排序", select_sort},
  {QUICK_SORT , "快速排序[尾元素作为主元]", quick_sort},
  {QUICK_SORT2, "快速排序[随机主元]", random_quick_sort},
  {HEAP_SORT  , "堆排序" ,  heap_sort},
};
static size_t s_func_map_size = sizeof(s_func_map)/sizeof(s_func_map[0]);
static char* sort_func_name_print()
{
  static char name[1024]={0};
  for (int i = 0; i < s_func_map_size; i++)
  {
    char n[128]; //128 enough 
    snprintf(n, 128, "\t%d: %s\n", (int)s_func_map[i].type, s_func_map[i].algorithm_name);
    snprintf(name+strlen(name), 1024, "%s", n);
  }
  return name;
}

static void print_help()
{
  printf("=============================================\n");
  printf("sortwrk usage():\n");
  printf("-t : 选择排序算法\n");
  printf("%s", sort_func_name_print());
  printf("-f : 输入数据文件的路径[deafult ./testdata.txt]\n");
  printf("-d : 打印排序前后数组[default 0]\n\n");
  printf("examples:\n");
  printf("     sortwrk -t 1 -f ./testdata.txt -d\n");
  printf("=============================================\n\n\n");
}


static int show_detail = 0;
static int algorithm = 0;
static char *file_path = "./testdata.txt"; //default file path

int main(int argc, char *argv[])
{
    int opt;
    while((opt =getopt(argc,argv,"t:f:d"))!= -1)
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
        case '?':
          print_help();
          break;
      }
    }
    int*test_array = NULL;
    int len = 0;
    int ret = read_array_from_file(file_path, &test_array, &len);
    if (ret != 0 || test_array == NULL || len <= 0)
      return 0;

    if (show_detail)
    {
      print_array("input array:", test_array, len);
      printf("\n\n");
    }
    
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