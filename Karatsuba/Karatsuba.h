#pragma once
#include "intArr.h"
namespace Mult
{
	class Karatsuba
	{
	private:
		int _n;
		intArr _x;
		intArr _y;

	public:
		Karatsuba(intArr x,intArr y , int n);
		~Karatsuba();
		//bool inputCheck(char* n, int x[], int y[]) ;
		intArr addArrays(intArr arr1, intArr arr2);
		intArr subtractArrays(intArr arr1, intArr arr2);
		intArr getLeftDigits(intArr w, int sizeLeft);
		intArr getRightDigits(intArr w, int sizeLeft, int sizeRight);
		intArr KaratsubaRec(intArr x, intArr y, int size);
		int Max(int num1, int num2);
	};
}