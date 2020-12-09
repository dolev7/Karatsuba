#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <math.h>
#include "Karatsuba.h"

using namespace std;

namespace Mult
{
	Karatsuba::Karatsuba(int n, int x[], int y[])
	{
		_origSize = n;
		_n = n;
		_x = new int[n];
		_y = new int[n];
		_x = x;
		_y = y;
		_resRow = new int[2 * n];
		_currentRow = new int[2 * n];
		for (int i = 0; i < 2 * n; i++)
			_resRow[i] = _currentRow[i] = 0;
	}
	Karatsuba::~Karatsuba()
	{
		//  delete[] _currentRow;
		 // delete[] _resRow;
	}

	intArr Karatsuba::addArrays(intArr arr1, intArr arr2, int size)
	{
		intArr res(size + 1);
		for (int i = size-1; i>0; i--)
		{
			res.insert(i, arr1.getValueInPlace(i)+arr2.getValueInPlace(i));
			res.insert((i - 1) ,res.getValueInPlace(i-1) +res.getValueInPlace(i) / 10);
			res.insert((i) , res.getValueInPlace(i) % 10);
		}
		return res;
	}
	intArr Karatsuba::subtractArrays(intArr arr1, intArr arr2, int size)
	{
		intArr res = new int[size + 1];
		for (int i = 0; i <= size; i++)
			res[i] = 0;
		for (int i = size-1; i>0; i--)
		{
			res[i] += arr1[i]-arr2[i];
			if (res[i] < 0)
			{
				res[i] *= -1;
				res[i - 1] -= 1;
			}
		}
		return res;
	}
	void Karatsuba::print()
	{
		bool leadZero = true;
		cout << "the number is " << endl;
		for (int i = 0; i < 2 * _n; i++)
		{
			if (leadZero)
			{
				if (_resRow[i] != 0)
					leadZero = false;
			}
			if (!leadZero)
				cout << _resRow[i] << " ";
		}
	}

	intArr Karatsuba::getLeftDigits(intArr w, int sizeLeft, int sizeRight)
	{
		//need "new" - I imagine you do it with dynamic array
		int end;
		if (sizeRight % 2 != 0)
			end = (sizeRight * 2) - 2;
		else
			end = (sizeRight * 2) - 1;
		for (int i = 1; i <= sizeLeft; i++)
		{
			w[end - i+1] = w[sizeLeft-i];
			w[sizeLeft - i] = 0;
		}
		return w;
	}

	intArr Karatsuba::getRightDigits(intArr w, int sizeLeft)
	{
		//need "new" - I imagine you do it with dynamic array
		for (int i = 0; i < sizeLeft; i++)
			w.insert(i , 0);
		return w;
	}

	intArr Karatsuba::KaratsubaRec(intArr x, intArr y, int size)
	{
		if (size < 2)
		{
			_resRow[(_origSize * 2) - 2] = (_x[_origSize - 1] * _y[_origSize - 1]) / 10;
			_resRow[(_origSize * 2) - 1] = (_x[_origSize - 1] * _y[_origSize - 1]) % 10;
			return _resRow;
		}

		//max length divided and rounded up
		int sizeLeft = (size / 2) + (size % 2);
		int sizeRight = size / 2;

		intArr a(sizeLeft), b(sizeRight), c(sizeLeft), d(sizeRight);

		a = getLeftDigits(x,sizeLeft, sizeRight);
		b = getRightDigits(x,size);
		c = getLeftDigits(y,size);
		d = getRightDigits(y,size);

		//dynamicArray z0(size), z1(size+1), z2(size);

		//z0 = KaratsubaRec(a, c, size);
		//z1 = KaratsubaRec(addRows(a + b),addRows (c + d), size+1);
		//z2 = KaratsubaRec(b, d, size);


		//return addArrays(addArrays(z0 , (((SubtractArrays(SubtractArrays(z1,z0)),z2)) * multiplier) , KaratsubaRec(z2 , (long long)(pow(10, 2 * N))));


	}
}
