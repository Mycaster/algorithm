#include "find_kth_node.h"

static int find_kth_node_init();
static int find_kth_node_run();
static const char* find_kth_node_print();
static const char* find_kth_node_print_after();
const struct list_op s_find_op = 
{
    find_kth_node_init,
    find_kth_node_run,
    find_kth_node_print,
    find_kth_node_print_after
};

static ListNode * head = NULL;
static char *filepath = "./list_testdata.txt";
static int k = 0;
static ListNode* k_node = NULL;
static int find_kth_node_init()
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
    srand(get_system_time_us());
    k = rand()%(n_count+3);
    printf("rand k=%d", k);
    return 0;
}

static ListNode* find_kth_node()
{
    if (head==NULL)
        return NULL;
#if 0
    //没有头结点的时候
    ListNode* fast = head->next;
    while(--k)
    {
        if (fast)
            fast = fast->next;
    }
    if (fast) //长度小于 k
        return NULL;

    ListNode *slow = head->next;
    while(fast->next)
    {
        slow = slow->next;
        fast = fast->next;
    }
#endif

    ListNode* fast = head;
    int k2 = k;
    while(k2--)
    {
        if (fast)
            fast = fast->next;
    }
    if (fast==NULL) //长度小于 k
        return NULL;
    
    ListNode *slow = head;
    while(fast)
    {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}

static int find_kth_node_run()
{
    if (k<=0)
        return 0;
    k_node = find_kth_node();
    return 0;
}

static const char* find_kth_node_print()
{
    return print_list(head);
}

static const char* find_kth_node_print_after()
{
    static char temp[1024];
    memset(temp, 0, 1024);
    snprintf(temp, 1024, "倒数第 %d 个节点为 %d\n", k, k_node == NULL ? -9999 : k_node->value);
    return temp;
}