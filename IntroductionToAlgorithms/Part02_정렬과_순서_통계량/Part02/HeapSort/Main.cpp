#include <cstdio>

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

void BuildMaxHeap(int *A)
{
	g_HeapSize = HEAPSIZE;

	for (int i = HEAPSIZE / 2; i >= 1; i--)
		MaxHeapify(A, i);
}

void HeapSort(int *A)
{
	BuildMaxHeap(A);
	for (int i = HEAPSIZE; i >= 2; i--)
	{
		int temp = A[1];
		A[1] = A[i];
		A[i] = temp;

		g_HeapSize = g_HeapSize - 1;
		MaxHeapify(A, 1);
	}
}


int main()
{
	int A[HEAPSIZE + 1] = { 0, 16, 14, 10, 8, 7, 9, 3, 2, 4, 1 };
	HeapSort(A);
}