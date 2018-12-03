#include "merge_sorted_list.h"

static int merge_sorted_list_init();
static int merge_sorted_list_run();
static const char* merge_sorted_list_print();
const struct list_op s_merge_sorted_list_op = 
{
    merge_sorted_list_init,
    merge_sorted_list_run,
    merge_sorted_list_print
};


static ListNode * list1 = NULL;
static ListNode * list2 = NULL;
static char *filepath = "./list_testdata.txt";
static int merge_sorted_list_init()
{
    //读取第1行的数据
    if (list1 == NULL)
    {
        int *array = NULL;
        int n_count = 0;
        int ret = read_array_from_file(filepath, &array, &n_count, 1);
        if (ret != 0)
        {
            printf("read_array_from_file failed, ret=%d", ret);
            return -1;
        }
        qsort(array, n_count, sizeof(int));
        list1 = create_list(array, n_count);
    }
    //读取第2行的数据
    if (list2 == NULL)
    {
        int *array = NULL;
        int n_count = 0;
        int ret = read_array_from_file(filepath, &array, &n_count, 2);
        if (ret != 0)
        {
            printf("read_array_from_file failed, ret=%d", ret);
            return -1;
        }
        qsort(array, n_count, sizeof(int));
        list2 = create_list(array, n_count);
    }
    return 0;
}

static int merge_sorted_list_run()
{
    return 0;
}

static const char* merge_sorted_list_print()
{
    
    return "Nil";
}
