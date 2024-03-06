#include <cstdio>

int Partition(int *A, int p, int r)
{
	int x = A[r];
	int i = p - 1;
	for (int j = p; j < r; j++)
	{
		if (A[j] <= x)
		{
			i = i + 1;
			int temp = A[i];
			A[i] = A[j];
			A[j] = temp;
		}
	}

	int temp = A[i + 1];
	A[i + 1] = A[r];
	A[r] = temp;

	return i + 1;
}

void QuickSort(int *A, int p, int r)
{
	if (p < r)
	{
		int q = Partition(A, p, r);
		QuickSort(A, p, q - 1);
		QuickSort(A, q + 1, r);
	}
}


int main()
{
	int A[9] = { 0, 2, 8, 7, 1, 3, 5, 6, 4 };
	QuickSort(A, 1, 8);


}