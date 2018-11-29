#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void print_help()
{
  printf("======================================\n");
  printf("sortwrk usage():\n");
  printf("-t : 选择排序算法\n");
  printf("     1: 插入排序\n");
  printf("     2: 快速排序\n");
  printf("     3: 堆排序\n");
  printf("-f : 输入数据文件的路径[deafult ./testdata.txt]\n");
  printf("-d : 打印排序前后数组[default 0]\n\n");
  printf("examples:\n");
  printf("     sortwrk -t 1 -f ./testdata.txt -d\n");
  printf("=======================================\n\n\n");
}


void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

void print_array(const char* str, const int *arr, int len)
{
  printf("%s\n", str);
  for (int i = 0; i < len; i++)
  {
    if (i!=0 && i%24==0)
    {
      printf("%d\n", arr[i]);
    }
    else
    {
      printf("%d\t", arr[i]);
    }
  }
  printf("\n");
}


int read_array_from_file(const char *file_path, int** array, int *n_array)
{
	if (file_path == NULL)
	{
    printf("filepath not invalid!! \n");
    return -1;
	}

	int *test_array = NULL;
	int n_test_array = 0;

	FILE *fp = fopen(file_path, "r+");
	if (fp == NULL)
	  {
  	printf("file not exists!! \n");
  	return -1;
	}

	int size = 0;
	while(!feof(fp))
  {
  	if (size == 0)
  	{
  		fscanf(fp,"%d",&size);
  		if (size != 0)
  		{
    		test_array = (int *)calloc(size, sizeof(int));
  		}
  		else
  		{
    		printf("array size is 0");
    		return -1;  
  		}
  	}
  	else
    {
    	fscanf(fp,"%d",&test_array[n_test_array++]);
  	}
	}
	fclose(fp);
	*array = test_array;
	*n_array = n_test_array-1; //加多了一次
	return 0;
}


int64_t get_system_time_us()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (tv.tv_sec * 1000000L + tv.tv_usec);
}


int64_t get_system_time_ms()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (tv.tv_sec * 1000L + tv.tv_usec/1000L);
}