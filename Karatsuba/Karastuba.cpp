#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <vector>
#include "Karatsuba.h"
using namespace std;

namespace Mult
{
	Karatsuba::Karatsuba(intArr x , intArr y, int n)
	{
		_x = x;
		_y = y;
		_n = n;
	}
	Karatsuba::~Karatsuba()
	{
		//  delete[] _currentRow;
		 // delete[] _resRow;
	}

	intArr Karatsuba::addArrays(intArr arr1, intArr arr2)
	{
		int size1 =arr1.getSize();
		int size2 = arr2.getSize();
		int maxSize = size1;
		if (size1 > size2)
		{
			arr2=arr2.AddZeros(size1 - size2);
			maxSize = size1;
		}
		if (size1 < size2)
		{
			arr1=arr1.AddZeros(size2 - size1);
			maxSize = size2;
		}
		intArr res(maxSize+1);
		for (int i = maxSize, j = 1; i > 0; i--, j++)
		{
			res.insert(i, res.get(i) + arr1.get(maxSize - j) + arr2.get(maxSize - j));
			res.insert((i - 1), res.get(i - 1) + res.get(i) / 10);
			res.insert((i), res.get(i) % 10);
		}
		if (res.getActualSize() != res.getSize())
			res.cutLeadingZeros();
		return res;
	}
	intArr Karatsuba::subtractArrays(intArr arr1, intArr arr2)
	{
		int size1 = arr1.getSize();
		int size2 = arr2.getSize();
		int maxSize = size1;
		if (size1 > size2)
		{
			arr2=arr2.AddZeros(size1 - size2);
			maxSize = size1;
		}
		if (size1 < size2)
		{
			arr1.AddZeros(size2 - size1);
			maxSize = size2;
		}
		intArr res(maxSize); 
		for (int i = maxSize-1, j=1; i >=0; i--, j++)
		{
			res.insert(i, res.get(i)+arr1.get(maxSize-j)- arr2.get(maxSize - j));
			if (res.get(i) < 0 && i>0)
			{
				res.insert(i, res.get(i) +10);
				res.insert(i-1,-1);
			}
		}
		if (res.getActualSize() != res.getSize())
			res.cutLeadingZeros();
		return res;
	}
	intArr Karatsuba::getLeftDigits(intArr w)
	{
		int size = w.getSize() / 2;
		if (size == 0)
		{
			w.insert(0, 0);
			return w;
		}
		intArr toreturn(size);
		for (int i = 0; i <size; i++)
		{
			toreturn.insert(i, w.get(i));
		}
		return toreturn;
	}
	intArr Karatsuba::getRightDigits(intArr w)
	{
		int wsize = w.getSize();
		if (wsize <= 1)
			return w;
		int start = wsize / 2;
		int size = start;
		if (wsize % 2 == 1)
			size++;
		intArr toreturn(size);
		int j = 0;
		for (int i = start; i < wsize; i++,j++)
				toreturn.insert(j, w.get(i));
		if (toreturn.getActualSize() != toreturn.getSize())
			toreturn.cutLeadingZeros();
		return toreturn;
	}
	intArr Karatsuba::KaratsubaRec(intArr x, intArr y, int size)
	{
		if (x.getActualSize() == 0 || y.getActualSize() == 0)
		{
			intArr zero(1);
			zero.insert(0, 0);
			return zero;
		}
		int sizeX = x.getSize();
		int sizeY = y.getSize();
		size = sizeX;
		if (sizeX > sizeY)
			y = y.AddZeros(sizeX - sizeY);
		if (sizeX < sizeY)
		{
			x = x.AddZeros(sizeY - sizeX);
			size = sizeY;
		}
		if (size < 2)
		{
			static int counter = 1;
			intArr baseCase(2);
			if (x.getActualSize() != x.getSize())
				x.cutLeadingZeros();
			if (y.getActualSize() != y.getSize())
				y.cutLeadingZeros();
			baseCase.insert(1, ((x.get(0) * y.get(0)) % 10));
			if (((x.get(0) * y.get(0)) / 10) != 0)
				baseCase.insert(0, ((x.get(0) * y.get(0)) / 10));
			else
				baseCase.cutLeadingZeros();
			counter++;
			return baseCase;
		}
		int sizeLeft = size / 2;
		int sizeRight = (size / 2) + (size % 2);
		intArr a(sizeLeft), b(sizeRight), c(sizeLeft), d(sizeRight);
		a = getLeftDigits(x);
		b = getRightDigits(x);
		c = getLeftDigits(y);
		d = getRightDigits(y);

		intArr z0(size), z1(size + 1), z2(size);
		z0 = KaratsubaRec(a, c, sizeLeft);
		z1 = KaratsubaRec(addArrays(a, b), addArrays(c, d),sizeLeft+1);
		z2 = KaratsubaRec(b, d, sizeRight);
		intArr shiftedz0((sizeLeft * 2)), shiftedZ1z0z2(sizeLeft);
		shiftedz0 = z0;
		shiftedz0.shiftLeft(size+size%2);
		shiftedZ1z0z2 = subtractArrays(subtractArrays(z1, z0), z2);
		shiftedZ1z0z2.shiftLeft(sizeRight);
		return addArrays(addArrays(shiftedz0, shiftedZ1z0z2), z2);
	}
}
