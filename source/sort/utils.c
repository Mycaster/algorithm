#include "utils.h"

static int log_level = 0;
void set_log_level(int level)
{
	log_level = level;
}
int get_log_level()
{
	return log_level;
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
			printf("%d \n", arr[i]);
		else
			printf("%d ", arr[i]);
	}
	printf("\n\n");
}


int read_array_from_file(const char *file_path, int** array, int *n_array)
{
	if (file_path == NULL)
	{
		LOGTRACE("filepath not invalid!!");
		return -1;
	}
	if (array == NULL || n_array == NULL)
		return -1;

	int *test_array = NULL;
	int n_test_array = 0;

	FILE *fp = fopen(file_path, "r+");
	if (fp == NULL)
	{
		LOGTRACE("file not exists!!");
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
				LOGTRACE("array size is 0");
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