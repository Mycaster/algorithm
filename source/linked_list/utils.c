#include "utils.h"

const char *print_list(ListNode *head)
{
    static char list_str[1024];
    memset(list_str, 0, sizeof(list_str));
    if (head == NULL)
        return "Nil";
    
    //头节点
    snprintf(list_str+strlen(list_str), 1024, "head->");
    ListNode *p = head->next;
    while(p)
    {
        if (p->next == NULL) //最后一个节点
        {
            snprintf(list_str+strlen(list_str), 1024, "%d", p->value);
            break;
        }
        else
        {
            snprintf(list_str+strlen(list_str), 1024, "%d->", p->value);
            p = p->next;
        }
    }
    snprintf(list_str+strlen(list_str), 1024, "\n");
    return list_str;
}

static ListNode* create_list_node(int value)
{
    // printf("create_list_node: %d\n", value);
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    node->value = value;
    node->next = NULL;
    return node;
}

static void delete_list_node(ListNode* node)
{
    if (node)
    {
        free(node);
    }
}

//带头链表
ListNode* create_list(int *arr, int len)
{
    ListNode* head = create_list_node(0);
    if (head == NULL)
    {
        printf("create_list_head failed\n");
        return NULL;
    }

    ListNode *p = head;
    for (int i = 0; i < len ; i++)
    {
        p->next = create_list_node(arr[i]);
        p = p->next;
    }
    return head;
}
void destory_list(ListNode *head)
{
    while(head)
    {
        ListNode* tmp = head;
        delete_list_node(tmp);
        head = head->next;
    }
}

//插入
int insert_node(ListNode *head, int value, int position)
{
    //默认插入到链表结尾处
    if (position <= 0)
    {

    }
    return 0;
}

//从链表中删除一个元素
int delete_node(ListNode *head, int value)
{
    return 0;
}



int64_t get_system_time_us()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000L + tv.tv_usec);
}

//读取指定行
int read_array_from_file(const char *file_path, int** array, int *n_array, int line)
{
	int *read_arr = NULL;
	int n_read_arr = 0;
	FILE *fp = fopen(file_path, "r+");
	if (fp == NULL)
    {
        printf("file not exists!! \n");
        return -1;
	}

	int size = 0;
    char line_str[1024] = {0};
    int n_line = 0;
	while(!feof(fp))
    {
        fgets(line_str, 1024, fp);
        // printf("%s", line_str);
        n_line++;
        if (n_line == line)
        {
            char *p = strtok(line_str, " ");
            size = atoi(p);
            if (size != 0)
            {
                read_arr = (int *)calloc(size, sizeof(int));
            }
            else
            {
                printf("array size is 0");
                return -1;
            }
            while((p=strtok(NULL, " "))!=NULL)
            {
                if (isdigit(*p))
                {
                    read_arr[n_read_arr++] = atoi(p);
                    // printf("%d\n", read_arr[n_read_arr-1]);
                }
            }
            break;
        }
	}
	fclose(fp);
	*array = read_arr;
	*n_array = n_read_arr-1; //加多了一次
	return 0;
}