#include "utils.h"

static int partition(int *arr, int start, int end, int rand_p)
{
    int i = start-1;
    int j = start;

    if (rand_p)
    {
        int random_index = rand()%(end-start+1)+start;
        // printf("random_index choose=%d[%d],\n", random_index, arr[random_index]);
        swap(&arr[random_index], &arr[end]);
    }

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

static int _qsort(int *arr, int start, int end, int rand_p)
{
    if (start < end)
    {
        int q = partition(arr,start,end,rand_p);
        _qsort(arr, start, q-1,rand_p);
        _qsort(arr, q+1, end,rand_p);
    }
    return 0;
}

int quick_sort(int *arr, int len)
{
    return _qsort(arr, 0, len-1, 0);
}

int random_quick_sort(int *arr, int len)
{
    srand(get_system_time_us());
    return _qsort(arr, 0, len-1, 1);
}