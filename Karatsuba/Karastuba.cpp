#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <vector>
#include "Karatsuba.h"
#include "KStack.h"

static const int START = -1;
static const int AFTER_FIRST = -2;
static const int AFTER_SECOND = -3;
static const int AFTER_THIRD = -4;

using namespace std;

namespace Mult
{
	Karatsuba::Karatsuba(intArr x, intArr y, int n)
	{
		_x = x;
		_y = y;
		_n = n;
	}

	intArr Karatsuba::addArrays(intArr arr1, intArr arr2)
	{
		int size1 = arr1.getSize();
		int size2 = arr2.getSize();
		int maxSize = size1;
		if (size1 > size2)
		{
			arr2 = arr2.AddZeros(size1 - size2);
			maxSize = size1;
		}
		if (size1 < size2)
		{
			arr1 = arr1.AddZeros(size2 - size1);
			maxSize = size2;
		}
		intArr res(maxSize + 1);
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
			arr2 = arr2.AddZeros(size1 - size2);
			maxSize = size1;
		}
		if (size1 < size2)
		{
			arr1.AddZeros(size2 - size1);
			maxSize = size2;
		}
		intArr res(maxSize);
		for (int i = maxSize - 1, j = 1; i >= 0; i--, j++)
		{
			res.insert(i, res.get(i) + arr1.get(maxSize - j) - arr2.get(maxSize - j));
			if (res.get(i) < 0 && i > 0)
			{
				res.insert(i, res.get(i) + 10);
				res.insert(i - 1, -1);
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
		for (int i = 0; i < size; i++)
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
		for (int i = start; i < wsize; i++, j++)
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
		z1 = KaratsubaRec(addArrays(a, b), addArrays(c, d), sizeLeft + 1);
		z2 = KaratsubaRec(b, d, sizeRight);
		intArr shiftedz0((sizeLeft * 2)), shiftedZ1z0z2(sizeLeft);
		shiftedz0 = z0;
		shiftedz0.shiftLeft(size + size % 2);
		shiftedZ1z0z2 = subtractArrays(subtractArrays(z1, z0), z2);
		shiftedZ1z0z2.shiftLeft(sizeRight);
		return addArrays(addArrays(shiftedz0, shiftedZ1z0z2), z2);
	}
	void Karatsuba::KaratsubaRecStarter(intArr x, intArr y, int n, intArr& res)
	{
		res = KaratsubaRec(x, y, n);
	}

	intArr Karatsuba::KaratsubaIterative(intArr x, intArr y, int size)
	{
		KStack S;
		S.MakeEmpty();
		intArr res(2 * size);
		Item Curr(x, y, size, res, START);
		bool returnFromRecursion = false;
		intArr temp;
		do
		{
			if (returnFromRecursion)
				Curr = S.Pop();
			if (Curr._line == START)
			{
				if (Curr._x.getActualSize() == 0 || Curr._y.getActualSize() == 0)
				{
					intArr zero(1);
					Curr._returnVal = zero;
					temp = zero;
					returnFromRecursion = true;
				}
				else if (Curr._x.getActualSize() != 0 && Curr._y.getActualSize() != 0)
				{
					int sizeX = Curr._x.getSize();
					int sizeY = Curr._y.getSize();
					size = sizeX;
					if (sizeX > sizeY)
						Curr._y = Curr._y.AddZeros(sizeX - sizeY);
					if (sizeX < sizeY)
					{
						Curr._x = Curr._x.AddZeros(sizeY - sizeX);
						size = sizeY;
					}
					Curr._n = size;
					cout << "THE WORLD NOW IS || X:"; Curr._x.printArr(); cout << "|| Y:"; Curr._y.printArr(); cout << " || SIZE:" << size << endl;
					if (Curr._n < 2)
					{
						intArr baseCase(2);
						if (Curr._x.getActualSize() != Curr._x.getSize())
							Curr._x.cutLeadingZeros();
						if (Curr._y.getActualSize() != Curr._y.getSize())
							Curr._y.cutLeadingZeros();
						baseCase.insert(1, ((Curr._x.get(0) * Curr._y.get(0)) % 10));
						if (((Curr._x.get(0) * Curr._y.get(0)) / 10) != 0)
							baseCase.insert(0, ((Curr._x.get(0) * Curr._y.get(0)) / 10));
						else
							baseCase.cutLeadingZeros();
						Curr._returnVal = baseCase;
						temp = baseCase;
						returnFromRecursion = true;
					}
					else
					{
						Curr._line = AFTER_FIRST;
						S.Push(Curr);
						Curr._x = getLeftDigits(Curr._x);
						Curr._y = getLeftDigits(Curr._y);
						Curr._n = Curr._n / 2;
						Curr._line = START;
						returnFromRecursion = false;
					}
				}
			}
			else if (Curr._line == AFTER_FIRST)
			{
				Curr._line = AFTER_SECOND;
				Curr.ac = temp;
				S.Push(Curr);
				Curr._x = getRightDigits(Curr._x);
				Curr._y = getRightDigits(Curr._y);
				Curr._n = (Curr._n / 2) + (Curr._n % 2);
				Curr._line = START;
				returnFromRecursion = false;
			}
			else if (Curr._line == AFTER_SECOND)
			{
				Curr._line = AFTER_THIRD;
				Curr.z2 = temp;
				S.Push(Curr);
				Curr._x = addArrays(getLeftDigits(Curr._x), getRightDigits(Curr._x));
				Curr._y = addArrays(getLeftDigits(Curr._y), getRightDigits(Curr._y));
				Curr._n = Curr._n / 2 + 2;
				Curr._line = START;
				returnFromRecursion = false;
			}
			else if (Curr._line == AFTER_THIRD)
			{
				Curr.z0 = Curr.ac;
				Curr.abcd = temp;
				Curr.z1z0z2 = subtractArrays(subtractArrays(Curr.abcd, Curr.ac), Curr.z2);
				Curr.z0.shiftLeft(Curr._n + Curr._n % 2);
				Curr.z1z0z2.shiftLeft((Curr._n) / 2 + Curr._n % 2);

				cout << "summary where || X = "; Curr._x.printArr(); cout << "  || Y = "; Curr._y.printArr(); cout << endl;
				cout << "Z0 is: "; Curr.z0.printArr(); cout << " ||Shifted Z1Z0Z2 is: "; Curr.z1z0z2.printArr(); cout << " ||Z2 is: "; Curr.z2.printArr(); cout << endl;

				Curr.restemp = addArrays(addArrays(Curr.z0, Curr.z1z0z2), Curr.z2);
				Curr._returnVal = Curr.restemp;
				temp = Curr._returnVal;
				returnFromRecursion = 1;
			}
		} 
		while (!S.IsEmpty());
		return Curr._returnVal;
	}

	void Karatsuba::KaratsubaRec_Print_and_TimeMeasure(ofstream& myfile)
	{

		cout << "Karatsuba(recursive) : x * y = ";
		auto start = chrono::high_resolution_clock::now();
		ios_base::sync_with_stdio(false);
		intArr res(2 * _n);
		KaratsubaRecStarter(_x, _y, _n, res);
		auto end = chrono::high_resolution_clock::now();
		double time_taken = static_cast<double>(chrono::duration_cast<chrono::nanoseconds>(end - start).count());
		time_taken *= 1e-9;
		myfile << "Time taken by function <Karatsuba Recursive> is : " << fixed
			<< time_taken << setprecision(9);
		myfile << " sec" << endl;
		res.printArr();
	}

	void Karatsuba::KaratsubaIterative_Print_and_TimeMeasure(ofstream& myfile)
	{

		cout << "Karatsuba(iterative) : x * y = ";
		auto start = chrono::high_resolution_clock::now();
		ios_base::sync_with_stdio(false);
		intArr printIT = this->KaratsubaIterative(this->_x, this->_y, this->_n);
		auto end = chrono::high_resolution_clock::now();
		double time_taken = static_cast<double>(chrono::duration_cast<chrono::nanoseconds>(end - start).count());
		time_taken *= 1e-9;
		myfile << "Time taken by function <Karatsuba Recursive> is : " << fixed
			<< time_taken << setprecision(9);
		myfile << " sec" << endl;
		printIT.printArr();
	}


}
