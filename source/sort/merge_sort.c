#include "utils.h"


/**
 * 将有序数组 arr[start1...end1] 和 有序数组 arr[start2...end2] 合并成一个有序数组
*/
static int merge_two_array(int *arr, int start1, int end1, int start2, int end2)
{
    LOGTRACE("start1=%d, end1=%d, start2=%d, end2=%d", start1, end1, start2, end2);
    int total_size = end1-start1 + end2-start2 + 2;
    int *arr_result = calloc(total_size, sizeof(int));
    int n_arr_result = 0;

    int i = start1;
    int j = start2;
    while(i<=end1 && j<=end2)
    {
        if (arr[i] < arr[j])
            arr_result[n_arr_result++] = arr[i++];
        else
            arr_result[n_arr_result++] = arr[j++];
    }
    while(i<=end1)
    {
        arr_result[n_arr_result++] = arr[i++];
    }
    while(j<=end2)
    {
        arr_result[n_arr_result++] = arr[j++];
    }
    LOGTRACE("start1=%d, n_arr_result=%d", start1, n_arr_result);

    //copy from arr_result to arr
    for (int k = 0; k < n_arr_result; k++)
    {
        arr[start1++] = arr_result[k];
    }
    LOGTRACE("start1=%d, n_arr_result=%d", start1, n_arr_result);
    return 0;
}

static int merge_sort_recursion(int *arr, int start, int end)
{
    LOGTRACE("start=%d, end=%d\n", start, end);
    if (start>=end)
        return 0;
    
    int q = (start + end) / 2;
    merge_sort_recursion(arr, start, q);
    merge_sort_recursion(arr, q+1, end);
    merge_two_array(arr, start, q, q+1, end);
    return 0;
}


int merge_sort(int * arr, int len)
{
    if (arr == NULL || len == 0)
        return -1;

    merge_sort_recursion(arr, 0, len-1);
    return 0;
}