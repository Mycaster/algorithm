#include "stdio.h"
#include "utils.h"

static int partition(int *arr, int start, int end)
{
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

static int _qsort(int *arr, int start, int end)
{
    if (start<end)
    {
        int q = partition(arr,start,end);
        _qsort(arr, start, q-1);
        _qsort(arr, q+1, end);
    }
    return 0;
}

int quick_sort(int *arr, int len)
{
    return _qsort(arr, 0, len-1);
}

static int random_partition(int *arr, int start, int end)
{
    int i = start-1;
    int j = start;
    int random_index = (start+end)/2;
    swap(&arr[random_index], &arr[end]);

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

static int _random_qsort(int *arr, int start, int end)
{
    if (start<end)
    {
        int q = random_partition(arr,start,end);
        _random_qsort(arr, start, q-1);
        _random_qsort(arr, q+1, end);
    }
    return 0;
}

int random_quick_sort(int *arr, int len)
{
    return _random_qsort(arr, 0, len-1);
}