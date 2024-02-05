#include <stdio.h>

void InsertionSort(int *arr, int arrSize)
{
	for (int j = 1; j < arrSize; j++)
	{
		int key = arr[j];
		int i = j - 1;
		while (i >= 0 && arr[i] > key)
		{
			arr[i + 1] = arr[i];
			i--;
		}

		arr[i + 1] = key;
	}
}

int main()
{
	int arr[6] = { 6, 5, 4, 3, 2, 1};

	InsertionSort(arr, 6);

	for (int i = 0; i < 6; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}