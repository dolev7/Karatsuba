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
		intArr addArrays(intArr arr1, intArr arr2);
		intArr subtractArrays(intArr arr1, intArr arr2);
		intArr getLeftDigits(intArr w);
		intArr getRightDigits(intArr w);
		intArr KaratsubaRec(intArr x, intArr y, int size);
		void KaratsubaRec_Print_and_TimeMeasure(ofstream& myfile);
		intArr KaratsubaIterative(intArr x, intArr y, int size);
		void KaratsubaIterative_Print_and_TimeMeasure(ofstream& myfile);
		void KaratsubaRecStarter(intArr x, intArr y, int n ,intArr& res);
		void KaratsubaIterativeStarter(intArr x, intArr y, int n, intArr& res);	
	};
}