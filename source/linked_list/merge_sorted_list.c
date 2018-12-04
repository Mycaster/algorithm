#include "merge_sorted_list.h"

static int merge_sorted_list_init();
static int merge_sorted_list_run();
static const char* merge_sorted_list_print_before();
static const char* merge_sorted_list_print_after();
const struct list_op s_merge_sorted_list_op = 
{
    merge_sorted_list_init,
    merge_sorted_list_run,
    merge_sorted_list_print_before,
    merge_sorted_list_print_after
};


static ListNode * head1 = NULL;
static ListNode * head2 = NULL;
static char *filepath = "./list_testdata.txt";

static int integer_cmp(const void *keyval, const void *datum) 
{
    int i1 = *(int*)keyval;
    int i2 = *(int*)datum;
    return i1 - i2;
}
static int merge_sorted_list_init()
{
    //读取第1行的数据
    if (head1 == NULL)
    {
        int *array = NULL;
        int n_count = 0;
        int ret = read_array_from_file(filepath, &array, &n_count, 1);
        if (ret != 0)
        {
            printf("read_array_from_file failed, ret=%d", ret);
            return -1;
        }
        qsort(array, n_count, sizeof(int), &integer_cmp);
        head1 = create_list(array, n_count);
    }
    //读取第2行的数据
    if (head2 == NULL)
    {
        int *array = NULL;
        int n_count = 0;
        int ret = read_array_from_file(filepath, &array, &n_count, 2);
        if (ret != 0)
        {
            printf("read_array_from_file failed, ret=%d", ret);
            return -1;
        }
        qsort(array, n_count, sizeof(int), &integer_cmp);
        head2 = create_list(array, n_count);
    }
    return 0;
}
//递归
ListNode* merge_two_list_recursion(ListNode *l1, ListNode* l2)
{
    if (l1==NULL)
        return l2;
    if (l2==NULL)
        return l1;

    ListNode *result = NULL;
    if (l1->value < l2->value)
    {
        result = l1;
        result->next = merge_two_list_recursion(l1->next, l2);
    }
    else
    {
        result = l2;
        result->next = merge_two_list_recursion(l1, l2->next);
    }
    return result;
}
//非递归
ListNode* merge_two_list(ListNode *l1, ListNode* l2)
{
    if (l1==NULL)
        return l2;
    if (l2==NULL)
        return l1;

    //建一个虚拟的头节点
    ListNode head = {0, NULL};
    ListNode* tail = NULL;
    while(l1 && l2)
    {
        if (l1->value < l2->value)
        {
            //更新第一个尾节点
            if (tail == NULL)
            {
                tail = l1;
                head.next = tail; 
            }
            else
            {
                tail->next = l1;
                tail = tail->next;
            }
            l1 = l1->next;
        }
        else
        {
            if (tail == NULL)
            {
                tail = l2;
                head.next = tail;
            }
            else
            {
                tail->next = l2;
                tail = tail->next;
            }
            l2 = l2->next;
        }
        // printf("list1: %s", print_no_head_list(l1));
        // printf("list2: %s", print_no_head_list(l2));
        // printf("head: %s", print_no_head_list(head));
    }
    if (l1)
        tail->next = l1;
    if (l2)
        tail->next = l2;
    
    return head.next;
}

static int merge_sorted_list_run()
{
    if (head1 == NULL || head1->next == NULL)
    {
        head1 = head2;
        return 0;
    }
    if (head2 == NULL || head2->next == NULL)
        return 0;

    ListNode* l1 = head1->next;
    ListNode* l2 = head2->next;
    delete_list_node(head2);
    head1->next = merge_two_list(l1, l2);
    return 0;
}

static const char* merge_sorted_list_print_before()
{
    static char two_list_str[2048];
    memset(two_list_str, 0, sizeof(two_list_str));
    snprintf(two_list_str+strlen(two_list_str), 2048, "head1: %s", print_list(head1));
    snprintf(two_list_str+strlen(two_list_str), 2048, "head2: %s\n", print_list(head2));
    return two_list_str;
}

static const char* merge_sorted_list_print_after()
{
    static char list_str[2048];
    memset(list_str, 0, sizeof(list_str));
    snprintf(list_str+strlen(list_str), 2048, "list_merge: %s\n", print_list(head1));
    return list_str;
}