#include <stdio.h>
#include <stdint.h>
#include <windows.h>

int L[100];
int R[100];

void Merge(int *A, int p, int q, int r)
{
	int n1 = q - p + 1;
	int n2 = r - q;

	for (int i = 0; i < n1; i++)
	{
		L[i] = A[p + i];
	}

	for (int j = 0; j < n2; j++)
	{
		R[j] = A[q + j + 1];
	}

	L[n1] = INT32_MAX;
	R[n2] = INT32_MAX;

	int i = 0;
	int j = 0;

	for (int k = p; k <= r; k++)
	{
		if (L[i] <= R[j])
		{
			A[k] = L[i];
			i++;
		}
		else
		{
			A[k] = R[j];
			j++;
		}
	}
}

void MergeSort(int *A, int p, int r)
{
	if (p < r)
	{
		int q = (p + r) / 2;
		MergeSort(A, p, q);
		MergeSort(A, q + 1, r);
		Merge(A, p, q, r);
	}
}

int main()
{
	int a[] = { 5, 2, 4, 7, 1, 3, 2, 6};

	// startIdx, endIdx
	MergeSort(a, 0, 7);

	for (int i = 0; i < 8; i++)
	{
		printf("%d ", a[i]);
	}

	printf("\n");

	return 0;
}