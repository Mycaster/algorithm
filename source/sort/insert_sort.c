#include "utils.h"

/**
 * 插入排序
*/
int insert_sort(int *arr, int len)
{
	if (arr == NULL || len == 0)
		return -1;

	//从第二个元素开始
	for (int j=1; j < len; j++)
	{
		int key = arr[j];
		int i = j-1; //i 指向前一个元素
		//依次将大于 a[j] 的元素向后挪动，直到找到可以放a[j] 的地方
		while(i>=0 && arr[i]>key)
		{
			arr[i+1] = arr[i];
			i--;
		}
		//将 a[j] 放在这个地方，这里之所以i+1 是因为while 中进行了最后一次 i--
		arr[i+1] = key;
	}
	return 0;
}