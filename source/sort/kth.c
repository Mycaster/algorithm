#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

static int _partition(int *arr, int start, int end)
{
    int i = start-1;
    int j = start;
    int mid = (start+end)>>1;
	swap(&arr[mid], &arr[end]);

    int base = arr[end];
    for (; j < end; ++j)
    {
        if (arr[j] <= base)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i+1], &arr[end]);
    return i;
}


int kth(int *arr, int len, int k)
{
	if (arr == NULL || len <= 0 || k <= 0 || k > len)
		return -1;

	int start = 0;
	int end = len-1;
	int _index = _partition(arr, start, end);
	while(_index != k-1)
	{
		if (_index > k-1)
		{
			end = _index-1;
			_index = _partition(arr, start, end);
		}
		else
		{
			start = _index+1;
			_index = _partition(arr, start, end);
		}
	}
	LOGTRACE("find kth[%d]", k);
	for (int i = 0; i < k; i++)
	{
		LOGTRACE("%d", arr[i]);
	}
	LOGTRACE();
	return 0;
}