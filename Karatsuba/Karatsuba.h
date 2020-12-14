#pragma once
#include "intArr.h"
#include <chrono>
#include <fstream>
#include <iomanip>
using namespace std;
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
		Karatsuba() { _n = 0; };
		~Karatsuba();
		//bool inputCheck(char* n, int x[], int y[]) ;
		intArr addArrays(intArr arr1, intArr arr2);
		intArr subtractArrays(intArr arr1, intArr arr2);
		intArr getLeftDigits(intArr w);
		intArr getRightDigits(intArr w);
		intArr KaratsubaRec(intArr x, intArr y, int size);
		void KaratsubaRec_Print_and_TimeMeasure(ofstream& myfile);
		
	};
}