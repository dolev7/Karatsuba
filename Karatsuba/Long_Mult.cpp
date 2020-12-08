#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>

int* LongMult(int n, int x[], int y[]);
void multX_Ydigit(int n, int x[], int y, int currentRow[], int start);
void addRows(int n, int currentRow[], int resRow[], int start);

int* LongMult(int n, int x[], int y[])
{
	int* resRow = new int[2 * n];
	int* currentRow = new int[2 * n];
	for (int i = 0; i < 2 * n; i++)
		resRow[i] = currentRow[i] = 0;

	for (int i = 0; i < n; i++)
	{
		while (y[n - i - 1] != 0)
		{
			multX_Ydigit(n, x, y[n - i - 1], currentRow, (2 * n - i - 1));
			addRows(n, currentRow, resRow, (2 * n - i - 1));
		}
	}
	return resRow;
}

void multX_Ydigit(int n, int x[], int yDig, int currentRow[], int start)
{
	for (int k = 0, i=start; k < n; k++, i--)
	{
		if (x[n - k - 1] != 0)
		{
			currentRow[i] += x[n - k - 1] * yDig;
			currentRow[i - 1] = currentRow[i] / 10;
			currentRow[i] %= 10;
		}
		else
		{
			//need to update the place in x which is 0 (after it, all numbers will be 0, so you always don't need to run them)
			break;
		}
			
	}
}

void addRows (int n, int currentRow[], int resRow[], int start)
{
	for (int k = 0, i = start; k < n; k++, i--)
	{
		resRow[i] += currentRow[i];
		resRow[i - 1] += resRow[i] / 10; //wtf?
		resRow[i] %= 10;
	}
}