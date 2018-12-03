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

static int reverse_list_run()
{
    if (head==NULL)
        return -1;

    /**
     * 只需要考虑 reverse 的那2个节点，也就是 prev->curr  变成 prev<-curr
    */
    ListNode *prev = NULL; //将第一个节点之前的节点用一个虚拟的NULL节点表示，会简单很多
    ListNode* curr = head->next;//保存第一个节点
    head->next = NULL; //将头节点独立出来
    
    while(curr)
    {
        //reverse 之前，先保存 curr 的下一个节点，防止reverse 之后断链
        ListNode *next = curr->next;
        curr->next = prev; // reverse 操作

        //没有下一个节点，说明当前节点为原列表的最后一个节点
        if (next==NULL)
        {
            head->next = curr; //头节点指向原列表的最后一个节点
            break;
        }
        //指针前移，更新 prev 和 curr
        prev = curr;
        curr = next;
    }
    return 0;
}

static const char* reverse_list_print()
{
    return print_list(head);
}
