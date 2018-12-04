#include "utils.h"

typedef enum OP_TYPE
{
	REVERSE_LIST = 1,
  	MERGE_SORTED_LIST = 2,
	FIND_KTH = 3
}OP_TYPE;

typedef struct op_func_map
{
	OP_TYPE type;
  	char* op_name;
  	struct list_op *op;
}op_func_map;

extern const struct list_op s_reverse_op;
extern const struct list_op s_merge_sorted_list_op;
extern const struct list_op s_find_op;
static op_func_map s_func_map[]=
{
  	{REVERSE_LIST, 		"反转单链表",    (struct list_op*)&s_reverse_op},
  	{MERGE_SORTED_LIST, "合并有序单链表", (struct list_op*)&s_merge_sorted_list_op},
	{FIND_KTH, 			"查找单链表倒数第k个节点", (struct list_op*)&s_find_op},
};
static size_t s_func_map_size = sizeof(s_func_map)/sizeof(s_func_map[0]);
static char* op_func_name_print()
{
  	static char name[1024]={0}; //1024 enough
	memset(name, 0, sizeof(name));
  	for (int i = 0; i < s_func_map_size; i++)
  	{
		snprintf(name+strlen(name), 1024, "\t%d: %s\n", (int)s_func_map[i].type, s_func_map[i].op_name);
  	}
  return name;
}

static void print_help()
{
	printf("=============================================\n");
  	printf("opwrk usage():\n");
  	printf("-t : 选择链表操作\n");
	printf("%s", op_func_name_print());
	printf("-d : 打印操作过程[default 0]\n\n");
	printf("examples:\n");
	printf("     listopwrk -t 1 -d\n");
	printf("=============================================\n\n\n");
}


static int show_detail = 0;
static int op_type = 0;
int main(int argc, char *argv[])
{
    int opt;
    while((opt =getopt(argc,argv,"t:dha:"))!= -1)
    {
		switch (opt) 
		{
			case 't':
			op_type = atoi(optarg);
			break;
			case 'd':
			show_detail = 1;
			break;
			case 'h':
			case '?':
			print_help();
			return 0;
		}
    }
	int ret = 0;
    int find = 0;
    for (int i = 0; i < s_func_map_size; i++)
    {
		if ((int)s_func_map[i].type == op_type)
		{
			find = 1;
			struct list_op *op = s_func_map[i].op;
			//init first
			if ((ret=op->init()) != 0)
			{
				printf("%s init failed, ret=%d\n", s_func_map[i].op_name, ret);
				return 0;
			}
			if (show_detail)
			{
				printf("\n操作前的数据:\n%s", op->print_before());
			}
		
			int64_t start = get_system_time_us();
			op->run();
			int64_t end = get_system_time_us();
		
			printf("%s, 耗时[%ld 微秒]\n", s_func_map[i].op_name, end - start);
			if (show_detail)
			{
				printf("\n操作后的数据:\n%s", op->print_after());
			}
			break;
		}
    }
    if (!find)
    {
		printf("not find op_function, type=%d\n", op_type);
		print_help();
    }
    return 0;
}