#include "reverse_list.h"

static int reverse_list_init();
static int reverse_list_run();
static const char* reverse_list_print();
const struct list_op s_reverse_op = 
{
    reverse_list_init,
    reverse_list_run,
    reverse_list_print
};

static ListNode * head = NULL;
static char *filepath = "./list_testdata.txt";
static int reverse_list_init()
{
    if (head != NULL)
        return 0;

    int *array = NULL;
    int n_count = 0;
    int ret = read_array_from_file(filepath, &array, &n_count, 1);
    if (ret != 0)
    {
        printf("read_array_from_file failed, ret=%d", ret);
        return -1;
    }
    head = create_list(array, n_count);
    return 0;
}

// static ListNode *rever

static int reverse_list_run()
{
    if (head==NULL)
        return -1;

    ListNode *p = head->next;
    head->next = NULL;

    while(p)
    {
        ListNode* cur = p;
        ListNode* next = p->next;
        
        if (p->next)
        {
        }
        else
        {
            p-
        }
        
        
    }


    
    return 0;
}

static const char* reverse_list_print()
{
    return print_list(head);
}
