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

	intArr Karatsuba::addArrays(intArr arr1, intArr arr2, int size)
	{
		int j = size - 1;
		intArr res(size+1);
		for (int i = size; i>0; i--, j--)
		{
			res.insert(i, res.get(i) + arr1.get(j) + arr2.get(j));
			res.insert((i - 1), res.get(i - 1) + res.get(i) / 10);
			res.insert((i), res.get(i) % 10);
		}
		if (res.getActualSize() != res.getSize())
		{
			//res.resize();
			cout << "resize" << endl;
		}
		return res;
	}
	intArr Karatsuba::subtractArrays(intArr arr1, intArr arr2, int size)
	{
		int j = size - 1;
		intArr res(size);
		for (int i = size-1; i >= 0; i--, j--)
		{
			res.insert(i, res.get(i)+arr1.get(j)- arr2.get(j));
			if (res.get(i) < 0)
			{
				res.insert(i, res.get(i) +10);
				res.insert(i-1,-1);
			}
		}
		if (res.getActualSize() != res.getSize())
		{
			//res.resize();
			cout << "resize" << endl;
		}
		return res;
	}

	intArr Karatsuba::getLeftDigits(intArr w, int sizeLeft)
	{
		intArr toreturn(sizeLeft);
		for (int i = 0; i <sizeLeft; i++)
		{
			toreturn.insert(i, w.get(i));
		}
		return toreturn;
	}

	intArr Karatsuba::getRightDigits(intArr w, int sizeLeft,int sizeRight)
	{
		intArr toreturn(sizeRight);
		for (int i = 0; i < sizeRight; i++)
			toreturn.insert(i , w.get(sizeLeft+i));
		if (toreturn.getActualSize() != toreturn.getSize())
		{
			cout << "resize" << endl;
			//toreturn.resize();
		}
		return toreturn;
	}

	int Karatsuba::Max(int num1, int num2)
	{
		if (num1 >= num2)
			return num1;
		else
			return num2;
	}

	intArr Karatsuba::KaratsubaRec(intArr x, intArr y, int size)
	{
		cout << "THE WORLD NOW IS || X:"; x.printArr(); cout << "|| Y:"; y.printArr(); cout << " || SIZE:" << size << endl;
		if (size < 2)
		{
			static int counter = 1;
			intArr baseCase(2);
			if (x.getActualSize()!=x.getSize())
				x.insert(0, x.get(1));
			if (y.getActualSize()!=y.getSize())
				y.insert(0, y.get(1));

			baseCase.insert(0, ((x.get(0) * y.get(0)) / 10));
			baseCase.insert(1, ((x.get(0) * y.get(0)) % 10));
			cout << "Base Case No." << counter << " : "; baseCase.printArr(); cout << endl;
			counter++;
			return baseCase;
		}
		int sizeLeft = (size / 2) + (size % 2);
		int sizeRight = size / 2;

		intArr a(sizeLeft), b(sizeRight), c(sizeLeft), d(sizeRight);

		a = getLeftDigits(x, sizeLeft);
		b = getRightDigits(x, sizeLeft, sizeRight);
		c = getLeftDigits(y, sizeLeft);
		d = getRightDigits(y, sizeLeft, sizeRight);
		cout << "A:"; a.printArr(); cout << "|| B:"; b.printArr(); cout << "|| C:"; c.printArr(); cout << "|| D:"; d.printArr(); cout << endl;
		intArr z0(size), z1(size + 1), z2(size);

		z0 = KaratsubaRec(a, c, sizeLeft);
		intArr aplusb = addArrays(a, b, sizeLeft);
		intArr cplusd = addArrays(c, d, sizeRight);
		z1 = KaratsubaRec(aplusb, cplusd, Max(aplusb.getActualSize(),cplusd.getActualSize()));
		z2 = KaratsubaRec(b, d, sizeRight);

		intArr shiftedz0((sizeLeft * 2) + z0.getSize()), shiftedAllZeds(z1.getSize());
		shiftedz0.shiftLeft(sizeLeft);
		shiftedAllZeds = (subtractArrays((subtractArrays(z1, z0, z1.getSize())), z2, z1.getSize())).shiftLeft(sizeLeft);
		cout <<  "return line" << endl;
		intArr shiftedAddedZeds(sizeLeft);
		shiftedAddedZeds = addArrays(shiftedz0, shiftedAllZeds, Max(shiftedz0.getSize(), shiftedAllZeds.getSize()));
		return addArrays(shiftedAddedZeds, z2, Max(shiftedAllZeds.getSize(), z2.getSize()));
	}

}
