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
			arr2.AddLeadingZeros(size1 - size2);
			maxSize = size1;
		}
		if (size1 < size2)
		{
			arr1.AddLeadingZeros(size2 - size1);
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
			res.resize();
		return res;
	}
	intArr Karatsuba::subtractArrays(intArr arr1, intArr arr2)
	{
		
		int size1 = arr1.getSize();
		int size2 = arr2.getSize();
		int maxSize = size1;
		
		if (size1 > size2)
		{
			arr2.AddLeadingZeros(size1 - size2);
			maxSize = size1;
		}
		if (size1 < size2)
		{
			arr1.AddLeadingZeros(size2 - size1);
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
			res.resize();
		return res;
	}

	intArr Karatsuba::getLeftDigits(intArr w)
	{
		int size = w.getSize() / 2;
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
		int start = wsize / 2;
		int size = start;
		if (wsize % 2 == 1)
			size++;
		intArr toreturn(size);
		int j = 0;
		for (int i = start; i < wsize; i++,j++)
				toreturn.insert(j, w.get(i));
		if (toreturn.getActualSize() != toreturn.getSize())
			toreturn.resize();
		return toreturn;
	}

	int Karatsuba::Max(int num1, int num2)
	{
		if (num1 >= num2)
			return num1;
		else
			return num2;
	}
	bool Karatsuba::inputcheck(intArr x, intArr y, char* size)
	{
		return true;
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
			y.AddLeadingZeros(sizeX - sizeY);
		if (sizeX < sizeY)
		{
			x.AddLeadingZeros(sizeY - sizeX);
			size = sizeY;
		}
		//cout << "THE WORLD NOW IS || X:"; x.printArr(); cout << "|| Y:"; y.printArr(); cout << " || SIZE:" << size << endl;
		if (size < 2)
		{
			static int counter = 1;
			intArr baseCase(2);
			if (x.getActualSize() != x.getSize())
				x.resize();
			if (y.getActualSize() != y.getSize())
				y.resize();

			baseCase.insert(1, ((x.get(0) * y.get(0)) % 10));
			if (((x.get(0) * y.get(0)) / 10) != 0)
				baseCase.insert(0, ((x.get(0) * y.get(0)) / 10));
			else
				baseCase.resize();
		//	cout << "Base Case No." << counter << " : "; baseCase.printArr(); cout << endl;
			counter++;
			return baseCase;
		}
		int sizeRight = (size / 2) + (size % 2);
		int sizeLeft = size / 2;

		intArr a(sizeLeft), b(sizeRight), c(sizeLeft), d(sizeRight);

		if (x.getSize() > 1)
		{
			a = getLeftDigits(x);
			b = getRightDigits(x);
		}
		else
		{
			a.insert(0, 0);
			b = x;
		}
		if (y.getSize() > 1)
		{
			c = getLeftDigits(y);
			d = getRightDigits(y);
		}
		else 
		{
			c.insert(0, 0);
			d = y;
		}
		//cout << "A:"; a.printArr(); cout << "|| B:"; b.printArr(); cout << "|| C:"; c.printArr(); cout << "|| D:"; d.printArr(); cout << endl;
		intArr z0(size), z1(size + 1), z2(size);

		z0 = KaratsubaRec(a, c, sizeLeft);
		intArr aplusb = addArrays(a, b);
		intArr cplusd = addArrays(c, d);

		z1 = KaratsubaRec(aplusb, cplusd, Max(aplusb.getActualSize(),cplusd.getActualSize()));
		z2 = KaratsubaRec(b, d, sizeRight);

		intArr shiftedz0((sizeLeft * 2)),z1minusz0(z1.getSize()), shiftedZ1z0z2(sizeLeft);
		shiftedz0 = z0;
		int add = 0;
		if (size%2 == 1)
			add = 1;
		shiftedz0.shiftLeft(size+add);
		z1minusz0 = subtractArrays(z1, z0);
		shiftedZ1z0z2 = subtractArrays(z1minusz0, z2);	
		shiftedZ1z0z2.shiftLeft(sizeRight);
		//cout << "summary where || X = "; x.printArr(); cout << "  || Y = "; y.printArr(); cout << endl;
		//cout << "Z0 is: "; z0.printArr(); cout << " ||Z1 is: "; z1.printArr(); cout << " ||Z2 is: "; z2.printArr(); cout << endl;
		//cout << "shiftedz0 is :"; shiftedz0.printArr(); cout << " || shiftedZ1z0z2 is:"; shiftedZ1z0z2.printArr(); cout << endl;
		//cout << "return is : "; addArrays(addArrays(shiftedz0, shiftedZ1z0z2), z2).printArr(); cout << endl;
		return addArrays(addArrays(shiftedz0, shiftedZ1z0z2), z2);
	}
}
