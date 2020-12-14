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
		Karatsuba() {};
		~Karatsuba();
		//bool inputCheck(char* n, int x[], int y[]) ;
		intArr addArrays(intArr arr1, intArr arr2);
		intArr subtractArrays(intArr arr1, intArr arr2);
		intArr getLeftDigits(intArr w);
		intArr getRightDigits(intArr w);
		intArr KaratsubaRec(intArr x, intArr y, int size);
	};
}