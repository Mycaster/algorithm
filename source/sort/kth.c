#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

static int _partition(int *arr, int start, int end)
{
 //    int i = start-1;
 //    int j = start;
 //    int mid = (start+end)/2;
	// swap(&arr[mid], &arr[end]);

 //    int base = arr[end];
 //    for (; j < end; ++j)
 //    {
 //        if (arr[j] <= base)
 //        {
 //            i++;
 //            swap(&arr[i], &arr[j]);
 //        }
 //    }
 //    swap(&arr[i+1], &arr[end]);
    int i = start-1;
    int j = start;
    int base = arr[end];
    for (; j < end; ++j)
    {
        if (arr[j] <= base)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    i++;
    swap(&arr[i], &arr[end]);
    return i;
}


int kth(int *arr, int len, int k)
{
	if (arr == NULL || len <= 0 || k <= 0 || k > len)
		return -1;

	int start = 0;
	int end = len-1;
	int index = _partition(arr, start, end);
	while(index != k-1)
	{
		if (index > k-1)
		{
			end = index-1;
			index = _partition(arr, start, end);
		}
		else
		{
			start = index+1;
			index = _partition(arr, start, end);
		}
	}
	printf("find kth[%d]\n", k);
	for (int i = 0; i < k; i++)
	{
		printf("%d\t", arr[i]);
	}
	printf("\n");
	return 0;
}