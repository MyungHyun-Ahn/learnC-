#include <cstdio>
#include <stdint.h>

#define HEAPSIZE 10

#define PARANT(i) i / 2
#define LEFT(i) 2 * i
#define RIGHT(i) 2 * i + 1

int g_HeapSize;

void MaxHeapify(int *A, int i)
{
	int l = LEFT(i);
	int r = RIGHT(i);
	int largest;
	if (l <= g_HeapSize && A[l] > A[i])
		largest = l;
	else
		largest = i;

	if (r <= g_HeapSize && A[r] > A[largest])
		largest = r;

	if (largest != i)
	{
		int temp = A[i];
		A[i] = A[largest];
		A[largest] = temp;

		MaxHeapify(A, largest);
	}
}

int HeapMaximum(int *A)
{
	return A[1];
}

int HeapExtractMax(int *A)
{
	if (g_HeapSize < 1)
	{
		// error underflow
		throw 1;
	}

	int max = A[1];
	A[1] = A[g_HeapSize];
	g_HeapSize = g_HeapSize - 1;
	MaxHeapify(A, 1);
	return max;
}

void HeapIncreaseKey(int *A, int i, int key)
{
	if (key < A[i])
	{
		// 새로운 키가 현재 키보다 작다
		throw 1;
	}

	A[i] = key;

	while (i > 1 && A[PARANT(i)] < A[i])
	{
		int temp = A[i];
		A[i] = A[PARANT(i)];
		A[PARANT(i)] = temp;
		i = PARANT(i);
	}
}

void MaxHeapInsert(int *A, int key)
{
	g_HeapSize = g_HeapSize + 1;
	A[g_HeapSize] = INT32_MIN;
	HeapIncreaseKey(A, g_HeapSize, key);
}

int main()
{

}