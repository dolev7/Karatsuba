#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <math.h>
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

	intArr Karatsuba::addArrays(intArr arr1, intArr arr2, int size, int& sizeOfAdded)
	{
		int j = size - 1;
		bool leadZero = true;
		intArr res(size+1);
		for (int i = size; i>0; i--, j--)
		{
			res.insert(i, res.get(i)+arr1.get(j)+arr2.get(j));
			res.insert((i - 1) ,res.get(i-1) +res.get(i) / 10);
			res.insert((i) , res.get(i) % 10);
		}
		sizeOfAdded = res.getSize();
		for (int i = 0; i < size ; i++)
		{
			if (leadZero)
			{
				if (res.get(i) != 0)
					leadZero = false;
				else
					sizeOfAdded--;
			}
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
		return toreturn;
	}

	intArr Karatsuba::KaratsubaRec(intArr x, intArr y, int size)
	{
		cout << "THE WORLD NOW IS || X:"; x.printArr(); cout << "|| Y:"; y.printArr(); cout << " || SIZE:" <<size <<  endl;
		if (size<2)
		{
			static int counter = 1;
			intArr baseCase(2);
			if (x.get(0) == 0 && x.getSize()==2)
				x.insert(0, x.get(1));
			if (y.get(0) == 0 && y.getSize()==2)
				y.insert(0, y.get(1));

			baseCase.insert(0, ((x.get(0) * y.get(0)) / 10));
			baseCase.insert(1, ((x.get(0) * y.get(0)) % 10));
	//		cout << "Base Case No." << counter << " : "; baseCase.printArr(); cout << endl;
			counter++;
			return baseCase;
		}
		int sizeLeft = (size / 2) + (size % 2);
		int sizeRight = size / 2;

		intArr a(sizeLeft), b(sizeRight), c(sizeLeft), d(sizeRight);

		a = getLeftDigits(x,sizeLeft);
		b = getRightDigits(x,sizeLeft,sizeRight);
		c = getLeftDigits(y, sizeLeft);
		d = getRightDigits(y, sizeLeft,sizeRight);
		cout << "A:"; a.printArr(); cout << "|| B:"; b.printArr(); cout << "|| C:"; c.printArr(); cout << "|| D:"; d.printArr(); cout << endl;
		intArr z0(size), z1(size+1), z2(size);
		int sizeOfaplusb=0, sizeOfcplusd=0, max;

		z0 = KaratsubaRec(a, c, sizeLeft);
		intArr aplusb = addArrays(a, b, sizeLeft, sizeOfaplusb);
		intArr cplusd = addArrays(c, d, sizeRight, sizeOfcplusd);
		if (sizeOfaplusb >= sizeOfcplusd)
			max = sizeOfaplusb;
		else
			max = sizeOfcplusd;
		z1 = KaratsubaRec (aplusb, cplusd, max);
		z2 = KaratsubaRec (b, d, sizeRight);
		return addArrays(addArrays(z0, (subtractArrays((subtractArrays(z1, z0, sizeLeft)), z2, sizeLeft)).shiftLeft(sizeLeft), sizeLeft, sizeLeft), z2.shiftLeft(sizeLeft * 2), size,size);
		// need to fix bug
	}


}
