#include "utils.h"

int select_sort(int * arr, int len)
{
    if (arr == NULL || len <= 0)
        return -1;

    for (int i = 0; i < len; i++)
    {
        int minest = arr[i]; //当前位置中的最小值
        int index_minest = i;//当前位置中的最小值的下标
        for (int j = i+1; j < len; j++)
        {
            if (arr[j] < minest)
            {
                minest = arr[j]; //更新最小值
                index_minest = j;//更新最小值的下标
            }
        }
        if (index_minest != i)
        {
            swap(&arr[i], &arr[index_minest]);
        }
    }
    return 0;
}