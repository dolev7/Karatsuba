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
	Karatsuba::Karatsuba(intArr x , intArr y, int n)
	{
		_x = x;
		_y = y;
		_n = n;
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
	void Karatsuba::KaratsubaRecStarter(intArr x,intArr y, int n, intArr& res)
	{
		res=KaratsubaRec(x, y,n);
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

	intArr Karatsuba::KaratsubaIterative(intArr x, intArr y, int size)
	{
		/*
		Stack S;
		S.MakeEmpty();
		ItemType Curr(X, Y, n, res, START);
		int returnFromRecursion = 0;
		string temp;
		do{
			if (returnFromRecursion)
				Curr = S.pop();
			if (Curr.line == START) {
				while (Curr.X.size() < Curr.Y.size())
					Curr.X.insert(0, "0");
				while (Curr.X.size() > Curr.Y.size())
					Curr.Y.insert(0, "0");
				Curr.n = Curr.X.size();
				if (Curr.n == 1) {
					Curr.res = Pow_Ten(Curr.res, 2);
					Curr.multiply = (Curr.X[0] - '0') * (Curr.Y[0] - '0');
					Curr.res[Curr.res.size() - 2] = Curr.multiply / 10 + '0';
					Curr.res[Curr.res.size() - 1] = Curr.multiply % 10 + '0';
					temp = Curr.res;
					returnFromRecursion = 1;
				}
				else {
					Curr.line = AFTER_FIRST;
					S.Push(Curr);
					Curr.X = Curr.X.substr(0, Curr.n / 2);
					Curr.Y = Curr.Y.substr(0, Curr.n / 2);
					Curr.n = Curr.n / 2;
					Curr.line = START;
					returnFromRecursion = 0;
				}
			}
			else if (Curr.line == AFTER_FIRST) {
				Curr.line = AFTER_SECOND;
				Curr.sc = temp;
				S.Push(Curr);
				Curr.X = Curr.X.substr(Curr.n/2, Curr.n);
				Curr.Y = Curr.Y.substr(Curr.n / 2, Curr.n);
				Curr.n = ((Curr.n / 2)) + (Curr.n % 2));
				Curr.line = START;
				returnFromRecursion = 0;
			}
			else if (Curr.line == AFTER_SECOND)
			{
				Curr.line = AFTER_THIRD;
				Curr.bd = temp;
				S.Push(Curr);
				Curr.X = Long_Add(Curr.x.substr(0, Curr.n / 2), Curr.X.substr(Curr.n / Curr.n));
				Curr.Y = Long_Add(Curr.Y.substr(0, Curr.n / 2), Curr.Y.substr(Curr.n / 2, Curr.n));
				Curr.n = Curr.n / 2 + 2;
			}

			*/

			//_________________

			/*
			{
				KStack S; // Stack which simulates the recursion.
				S.MakeEmpty();
				Karatsuba k(x, y, size); // Values of current “recursive call”
				intArr returnval;
				Item Curr;
				Curr.k = k; Curr.line = START; Curr.returnVal = returnval;

				Item Next; // Values of next “recursive call”.

				Current.k = k;
				Current.line = START;
				KS.Push(Current);
				while (!KS.IsEmpty())
				{
					Current = KS.Pop();
					if (Current.line == START)
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
							Current.returnVal = baseCase;
						}
						else
						{
							Current.line = AFTER_FIRST;
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
							KS.Push(Current);
							// k.set-> change size/2;
							Next.k = Current.k;
							Next.line = START;
							KS.Push(Next);
						}
					}
					else if (Current.line == AFTER_FIRST)
					{
						Current.line = AFTER_SECOND;
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
						KS.Push(Current);
						// k.set-> change size/2;
						Next.k = Current.k;
						Next.line = START;
						KS.Push(Next);
					}
					else if (Current.line == AFTER_SECOND)
					{
						// In this case do nothing.
					}
					else if (Current.line == AFTER_THIRD)
					{ /*
						intArr shiftedz0((sizeLeft * 2)), shiftedZ1z0z2(sizeLeft);
						shiftedz0 = z0;
						shiftedz0.shiftLeft(size + size % 2);
						shiftedZ1z0z2 = subtractArrays(subtractArrays(z1, z0), z2);
						shiftedZ1z0z2.shiftLeft(sizeRight);
						return addArrays(addArrays(shiftedz0, shiftedZ1z0z2), z2);
					}

				}
				//return addArrays(AddArrays(Shiftedreturnedz0, Shiftedreturnedz1)returnedz2);
			}

		}
		*/
              return 0;
	}
}
